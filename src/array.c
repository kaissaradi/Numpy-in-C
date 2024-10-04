#include "array.h"
#include <stdlib.h>
#include <string.h>

#ifdef _OPENMP
#include <omp.h>
#endif

// Helper function to handle memory allocation errors
static void free_array_memory(ArrayType *arr) {
    if (arr) {
        free(arr->data);
        free(arr->shape);
        free(arr->strides);
        free(arr);
    }
}

// Function to calculate strides
void calculate_strides(const int *shape, int ndim, int *strides) {
    strides[ndim - 1] = 1;
    for (int i = ndim - 2; i >= 0; i--) {
        strides[i] = strides[i + 1] * shape[i + 1];
    }
}

// Function to create a new array
ArrayType* create_array(const int *shape, int ndim, ArrayError *error) {
    if (ndim <= 0 || shape == NULL) {
        if (error) *error = ARRAY_ERROR_INVALID_DIMENSION;
        return NULL;
    }

    ArrayType *arr = (ArrayType*)malloc(sizeof(ArrayType));
    if (!arr) {
        if (error) *error = ARRAY_ERROR_MEMORY_ALLOCATION;
        return NULL;
    }

    arr->ndim = ndim;
    arr->shape = (int*)calloc(ndim, sizeof(int));
    arr->strides = (int*)calloc(ndim, sizeof(int));
    if (!arr->shape || !arr->strides) {
        free_array_memory(arr);
        if (error) *error = ARRAY_ERROR_MEMORY_ALLOCATION;
        return NULL;
    }

    arr->size = 1;
    for (int i = 0; i < ndim; i++) {
        arr->shape[i] = shape[i];
        arr->size *= shape[i];
    }

    arr->itemsize = sizeof(float);
    arr->data = (float*)calloc(arr->size, arr->itemsize);
    if (!arr->data) {
        free_array_memory(arr);
        if (error) *error = ARRAY_ERROR_MEMORY_ALLOCATION;
        return NULL;
    }

    calculate_strides(arr->shape, ndim, arr->strides);

    if (error) *error = ARRAY_SUCCESS;
    return arr;
}

// Function to free an array
void free_array(ArrayType *arr) {
    free_array_memory(arr);
}

// Function to compare shapes and determine the broadcast shape
ShapeInfo* compare_shapes(const ArrayType *a, const ArrayType *b) {
    int max_ndim = (a->ndim > b->ndim) ? a->ndim : b->ndim;
    int *shape = (int*)calloc(max_ndim, sizeof(int));
    if (!shape) {
        return NULL;
    }

    for (int i = 0; i < max_ndim; i++) {
        int a_dim = (i < max_ndim - a->ndim) ? 1 : a->shape[i - (max_ndim - a->ndim)];
        int b_dim = (i < max_ndim - b->ndim) ? 1 : b->shape[i - (max_ndim - b->ndim)];
        if (a_dim != b_dim && a_dim != 1 && b_dim != 1) {
            free(shape);
            return NULL;  // Shapes are not compatible for broadcasting
        }
        shape[i] = (a_dim > b_dim) ? a_dim : b_dim;
    }

    ShapeInfo *info = (ShapeInfo*)malloc(sizeof(ShapeInfo));
    if (!info) {
        free(shape);
        return NULL;
    }

    info->ndim = max_ndim;
    info->shape = shape;
    return info;
}

// Function to calculate the linear index from multidimensional indices
size_t calculate_index(const int *indices, const int *shape, const int *strides, int ndim) {
    size_t index = 0;
    for (int i = 0; i < ndim; i++) {
        index += indices[i] * strides[i];
    }
    return index;
}

// Helper function for element-wise operations with broadcasting
ArrayError elementwise_operation(ArrayType **result, const ArrayType *a, const ArrayType *b, char op) {
    ShapeInfo *broadcast_shape = compare_shapes(a, b);
    if (!broadcast_shape) {
        return ARRAY_ERROR_INVALID_DIMENSION;
    }

    int error_flag = 0;  // Flag to check if any error occurs

    // Create result array if it's NULL or has incorrect shape
    if (!*result || (*result)->ndim != broadcast_shape->ndim) {
        free_array(*result);
        *result = create_array(broadcast_shape->shape, broadcast_shape->ndim, NULL);
        if (!*result) {
            free(broadcast_shape->shape);
            free(broadcast_shape);
            return ARRAY_ERROR_MEMORY_ALLOCATION;
        }
    }

    int *strides_a = (int*)malloc(a->ndim * sizeof(int));
    int *strides_b = (int*)malloc(b->ndim * sizeof(int));
    int *strides_result = (int*)malloc((*result)->ndim * sizeof(int));

    if (!strides_a || !strides_b || !strides_result) {
        free(strides_a);
        free(strides_b);
        free(strides_result);
        free(broadcast_shape->shape);
        free(broadcast_shape);
        return ARRAY_ERROR_MEMORY_ALLOCATION;
    }

    calculate_strides(a->shape, a->ndim, strides_a);
    calculate_strides(b->shape, b->ndim, strides_b);
    calculate_strides((*result)->shape, (*result)->ndim, strides_result);

    int *indices = (int*)calloc((*result)->ndim, sizeof(int));
    if (!indices) {
        free(strides_a);
        free(strides_b);
        free(strides_result);
        free(broadcast_shape->shape);
        free(broadcast_shape);
        return ARRAY_ERROR_MEMORY_ALLOCATION;
    }

    // Initialize the result array to ensure no leftover values
    memset((*result)->data, 0, (*result)->size * sizeof(float));

#ifdef _OPENMP
    #pragma omp parallel for shared(error_flag)
#endif
    for (size_t i = 0; i < (*result)->size; i++) {
        if (error_flag) continue;  // Skip computation if an error has occurred

        // Calculate indices for a and b considering broadcasting
        size_t index_a = 0;
        size_t index_b = 0;
        size_t index_result = i;

        for (int j = 0; j < (*result)->ndim; j++) {
            size_t dim_index = (index_result / strides_result[j]) % (*result)->shape[j];
            if (j < a->ndim) index_a += (dim_index % a->shape[j]) * strides_a[j];
            if (j < b->ndim) index_b += (dim_index % b->shape[j]) * strides_b[j];
        }

        switch (op) {
            case '+':
                (*result)->data[i] = a->data[index_a] + b->data[index_b];
                break;
            case '*':
                (*result)->data[i] = a->data[index_a] * b->data[index_b];
                break;
            default:
                error_flag = 1;
                break;
        }
    }

    free(indices);
    free(strides_a);
    free(strides_b);
    free(strides_result);
    free(broadcast_shape->shape);
    free(broadcast_shape);

    if (error_flag) return ARRAY_ERROR_INVALID_DIMENSION;

    return ARRAY_SUCCESS;
}

// Function to add arrays element-wise with broadcasting
ArrayError add_arrays(ArrayType **result, const ArrayType *a, const ArrayType *b) {
    return elementwise_operation(result, a, b, '+');
}

// Function to multiply arrays element-wise with broadcasting
ArrayError multiply_arrays(ArrayType **result, const ArrayType *a, const ArrayType *b) {
    return elementwise_operation(result, a, b, '*');
}
