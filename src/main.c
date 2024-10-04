#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include "array.h"
#include "memory.h"

#define ARRAY_DIMS 2
#define ARRAY_ROWS 3
#define ARRAY_COLS 4

typedef enum {
    OPERATION_ADD,
    OPERATION_MULTIPLY
    // Add more operations as needed
} ArrayOperation;

// Function prototypes
static void print_array(const ArrayType *arr);
static int initialize_array(ArrayType *arr, float (*init_func)(size_t, size_t, const ArrayType *));
static float init_func_a(size_t i, size_t j, const ArrayType *arr);
static float init_func_b(size_t i, size_t j, const ArrayType *arr);
static int perform_operation(ArrayType **result, const ArrayType *a, const ArrayType *b, ArrayOperation op);
static void cleanup(MemoryPoolType *pool, ArrayType *arrays[], size_t array_count);
static void handle_error(const char *message, MemoryPoolType *pool, ArrayType *arrays[], size_t array_count);

int main(void) {
    MemoryPoolType *memory_pool = NULL;
    ArrayType *arrays[3] = {NULL};  // a, b, result
    const int shape[] = {ARRAY_ROWS, ARRAY_COLS};
    size_t array_count = sizeof(arrays) / sizeof(arrays[0]);

    printf("==================================================\n");
    printf(" Multidimensional Array Operations in C\n");
    printf("==================================================\n");

    // Calculate required memory
    size_t array_size = ARRAY_ROWS * ARRAY_COLS * sizeof(float);
    size_t pool_size = sizeof(ArrayType) * array_count + array_size * array_count;

    printf("--------------------------------------------------\n");
    printf("Creating memory pool of size %zu bytes...\n", pool_size);

    // Create memory pool
    if (!(memory_pool = create_memory_pool(pool_size))) {
        handle_error("Failed to create memory pool", NULL, NULL, 0);
        return EXIT_FAILURE;
    }

    printf("Memory pool created successfully.\n");
    printf("--------------------------------------------------\n");

    // Allocate and initialize arrays a and b
    for (int i = 0; i < 2; ++i) {
        arrays[i] = create_array(shape, ARRAY_DIMS, NULL);
        if (!arrays[i]) {
            handle_error("Failed to allocate arrays", memory_pool, arrays, array_count);
            return EXIT_FAILURE;
        }
    }

    // Initialize array a with custom values
    if (initialize_array(arrays[0], init_func_a) != 0) {
        handle_error("Failed to initialize array a", memory_pool, arrays, array_count);
        return EXIT_FAILURE;
    }

    // Initialize array b with custom values
    if (initialize_array(arrays[1], init_func_b) != 0) {
        handle_error("Failed to initialize array b", memory_pool, arrays, array_count);
        return EXIT_FAILURE;
    }

    // Print arrays before addition
    printf("Array a before addition:\n");
    print_array(arrays[0]);
    printf("Array b before addition:\n");
    print_array(arrays[1]);

    // Perform addition operation
    if (perform_operation(&arrays[2], arrays[0], arrays[1], OPERATION_ADD) != 0) {
        handle_error("Addition operation failed", memory_pool, arrays, array_count);
        return EXIT_FAILURE;
    }


    printf("Addition result:\n");
    print_array(arrays[2]);

    // Perform multiplication operation
    free_array(arrays[2]);
    arrays[2] = NULL;

    if (perform_operation(&arrays[2], arrays[0], arrays[1], OPERATION_MULTIPLY) != 0) {
        handle_error("Multiplication operation failed", memory_pool, arrays, array_count);
        return EXIT_FAILURE;
    }

    printf("Multiplication result:\n");
    print_array(arrays[2]);

    // Clean up
    cleanup(memory_pool, arrays, array_count);
    return 0;
}

// Function to print an array
static void print_array(const ArrayType *arr) {
    if (!arr || !arr->data) return;
    for (int i = 0; i < arr->shape[0]; ++i) {
        for (int j = 0; j < arr->shape[1]; ++j) {
            printf("%f ", arr->data[i * arr->shape[1] + j]);
        }
        printf("\n");
    }
}

// Function to initialize an array using a custom function
static int initialize_array(ArrayType *arr, float (*init_func)(size_t, size_t, const ArrayType *)) {
    if (!arr || !arr->data || !init_func) return -1;

    for (size_t i = 0; i < arr->shape[0]; ++i) {
        for (size_t j = 0; j < arr->shape[1]; ++j) {
            arr->data[i * arr->shape[1] + j] = init_func(i, j, arr);
        }
    }
    return 0;
}

// Custom initialization function for array a
static float init_func_a(size_t i, size_t j, const ArrayType *arr) {
    return (float)(i * arr->shape[1] + j + 1);
}

// Custom initialization function for array b
static float init_func_b(size_t i, size_t j, const ArrayType *arr) {
    return (float)((i * arr->shape[1] + j) * 2);
}

// Perform an operation (addition or multiplication) on two arrays
static int perform_operation(ArrayType **result, const ArrayType *a, const ArrayType *b, ArrayOperation op) {
    ArrayError error;
    switch (op) {
        case OPERATION_ADD:
            error = add_arrays(result, a, b);
            break;
        case OPERATION_MULTIPLY:
            error = multiply_arrays(result, a, b);
            break;
        default:
            fprintf(stderr, "Unknown operation\n");
            return -1;
    }

    if (error != ARRAY_SUCCESS) {
        fprintf(stderr, "Error performing array operation: %d\n", error);
        return -1;
    }
    return 0;
}

// Clean up and free memory
static void cleanup(MemoryPoolType *pool, ArrayType *arrays[], size_t array_count) {
    if (pool) {
        destroy_memory_pool(pool);
    }
    if (arrays) {
        for (size_t i = 0; i < array_count; ++i) {
            if (arrays[i]) {
                free_array(arrays[i]);
            }
        }
        memset(arrays, 0, array_count * sizeof(ArrayType*));
    }
}

// Handle errors by printing a message and cleaning up
static void handle_error(const char *message, MemoryPoolType *pool, ArrayType *arrays[], size_t array_count) {
    fprintf(stderr, "Error: %s\n", message);
    if (errno) {
        fprintf(stderr, "System error: %s\n", strerror(errno));
    }
    cleanup(pool, arrays, array_count);
}
