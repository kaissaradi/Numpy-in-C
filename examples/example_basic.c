#include <stdio.h>
#include "array.h"

void print_array(const ArrayType *arr) {
    for (int i = 0; i < arr->ndim; i++) {
        printf("[");
    }
    for (size_t i = 0; i < arr->size; i++) {
        printf("%f", arr->data[i]);
        for (int j = arr->ndim - 1; j >= 0; j--) {
            if ((i + 1) % arr->shape[j] == 0 && (i + 1) != arr->size) {
                printf("]");
                if (j != 0) {
                    printf("\n");
                    for (int k = 0; k < arr->ndim - j; k++) {
                        printf("[");
                    }
                }
            }
        }
        if (i + 1 != arr->size) {
            printf(", ");
        }
    }
    for (int i = 0; i < arr->ndim; i++) {
        printf("]");
    }
    printf("\n");
}

int main() {
    int shape[] = {2, 3};
    ArrayError error;
    ArrayType *a = create_array(shape, 2, &error);
    ArrayType *b = create_array(shape, 2, &error);
    ArrayType *result = create_array(shape, 2, &error);

    if (!a || !b || !result) {
        fprintf(stderr, "Failed to create arrays\n");
        return 1;
    }

    // Initialize arrays
    for (size_t i = 0; i < a->size; i++) {
        a->data[i] = (float)i;
        b->data[i] = (float)(i * 2);
    }

    // Perform addition
    error = add_arrays(result, a, b);
    if (error != ARRAY_SUCCESS) {
        fprintf(stderr, "Error adding arrays\n");
        free_array(a);
        free_array(b);
        free_array(result);
        return 1;
    }

    printf("Array a:\n");
    print_array(a);

    printf("Array b:\n");
    print_array(b);

    printf("Result of addition:\n");
    print_array(result);

    // Perform multiplication
    error = multiply_arrays(result, a, b);
    if (error != ARRAY_SUCCESS) {
        fprintf(stderr, "Error multiplying arrays\n");
        free_array(a);
        free_array(b);
        free_array(result);
        return 1;
    }

    printf("Result of multiplication:\n");
    print_array(result);

    // Free arrays
    free_array(a);
    free_array(b);
    free_array(result);

    return 0;
}
