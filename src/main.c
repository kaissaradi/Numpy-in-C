#include <stdio.h>
#include "array.h"
#include "memory.h"

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

    for (size_t i = 0; i < a->size; i++) {
        a->data[i] = (float)i;
        b->data[i] = (float)(i * 2);
    }

    error = add_arrays(result, a, b);
    if (error != ARRAY_SUCCESS) {
        fprintf(stderr, "Error adding arrays\n");
        free_array(a);
        free_array(b);
        free_array(result);
        return 1;
    }

    printf("Result of addition:\n");
    for (size_t i = 0; i < result->size; i++) {
        printf("%f ", result->data[i]);
    }
    printf("\n");

    free_array(a);
    free_array(b);
    free_array(result);

    return 0;
}
