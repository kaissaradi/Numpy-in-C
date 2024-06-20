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
        free(arr);
    }
}

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
    if (!arr->shape) {
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

    if (error) *error = ARRAY_SUCCESS;
    return arr;
}

void free_array(ArrayType *arr) {
    free_array_memory(arr);
}

ArrayError add_arrays(ArrayType *result, const ArrayType *a, const ArrayType *b) {
    if (!result || !a || !b) return ARRAY_ERROR_NULL_POINTER;
    if (a->ndim != b->ndim || a->ndim != result->ndim) return ARRAY_ERROR_INVALID_DIMENSION;

    for (int i = 0; i < a->ndim; i++) {
        if (a->shape[i] != b->shape[i] || a->shape[i] != result->shape[i]) {
            return ARRAY_ERROR_INVALID_DIMENSION;
        }
    }

#ifdef _OPENMP
    #pragma omp parallel for if (omp_get_max_threads() > 1)
#endif
    for (size_t i = 0; i < a->size; i++) {
        result->data[i] = a->data[i] + b->data[i];
    }

    return ARRAY_SUCCESS;
}

ArrayError multiply_arrays(ArrayType *result, const ArrayType *a, const ArrayType *b) {
    if (!result || !a || !b) return ARRAY_ERROR_NULL_POINTER;
    if (a->ndim != b->ndim || a->ndim != result->ndim) return ARRAY_ERROR_INVALID_DIMENSION;

    for (int i = 0; i < a->ndim; i++) {
        if (a->shape[i] != b->shape[i] || a->shape[i] != result->shape[i]) {
            return ARRAY_ERROR_INVALID_DIMENSION;
        }
    }

#ifdef _OPENMP
    #pragma omp parallel for if (omp_get_max_threads() > 1)
#endif
    for (size_t i = 0; i < a->size; i++) {
        result->data[i] = a->data[i] * b->data[i];
    }

    return ARRAY_SUCCESS;
}
