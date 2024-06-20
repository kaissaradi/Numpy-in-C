#include <stdio.h>
#include "array.h"
#include "memory.h"

int main() {
    int shape[] = {2, 3};
    ArrayError error;

    // Create a memory pool with sufficient size
    size_t pool_size = sizeof(ArrayType) * 3 + 6 * sizeof(float) * 3; // 3 arrays, each with 6 elements
    MemoryPoolType *memory_pool = create_memory_pool(pool_size);
    if (!memory_pool) {
        fprintf(stderr, "Failed to create memory pool\n");
        return 1;
    }

    // Allocate arrays from the memory pool
    ArrayType *a = allocate_from_pool(memory_pool, sizeof(ArrayType));
    ArrayType *b = allocate_from_pool(memory_pool, sizeof(ArrayType));
    ArrayType *result = allocate_from_pool(memory_pool, sizeof(ArrayType));
    if (!a || !b || !result) {
        fprintf(stderr, "Failed to allocate arrays\n");
        destroy_memory_pool(memory_pool);
        return 1;
    }

    // Initialize arrays using the memory pool
    a->data = allocate_from_pool(memory_pool, 6 * sizeof(float)); // 2*3
    b->data = allocate_from_pool(memory_pool, 6 * sizeof(float)); // 2*3
    result->data = allocate_from_pool(memory_pool, 6 * sizeof(float)); // 2*3

    if (!a->data || !b->data || !result->data) {
        fprintf(stderr, "Failed to allocate array data\n");
        destroy_memory_pool(memory_pool);
        return 1;
    }

    a->ndim = b->ndim = result->ndim = 2;
    a->shape = b->shape = result->shape = shape;
    a->size = b->size = result->size = 6;
    a->itemsize = b->itemsize = result->itemsize = sizeof(float);

    for (size_t i = 0; i < a->size; i++) {
        a->data[i] = (float)i;
        b->data[i] = (float)(i * 2);
    }

    error = add_arrays(result, a, b);
    if (error != ARRAY_SUCCESS) {
        fprintf(stderr, "Error adding arrays\n");
        destroy_memory_pool(memory_pool);
        return 1;
    }

    printf("Result of addition:\n");
    for (size_t i = 0; i < result->size; i++) {
        printf("%f ", result->data[i]);
    }
    printf("\n");

    // Clean up by destroying the memory pool
    destroy_memory_pool(memory_pool);
    return 0;
}
