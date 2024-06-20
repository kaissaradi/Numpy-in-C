#include <stdio.h>
#include <assert.h>
#include "array.h"
#include "memory.h"

// Helper function to print test results
void print_test_result(const char *test_name, int result) {
    printf("%s: %s\n", test_name, result ? "PASSED" : "FAILED");
}

// Function to test array creation
void test_create_array() {
    int shape[] = {2, 3};
    ArrayError error;
    ArrayType *arr = create_array(shape, 2, &error);
    int passed = arr != NULL && error == ARRAY_SUCCESS && arr->ndim == 2 &&
                 arr->size == 6 && arr->itemsize == sizeof(float) && arr->data != NULL;
    print_test_result("test_create_array", passed);
    free_array(arr);
}

// Function to test array addition
void test_add_arrays() {
    int shape[] = {2, 3};
    ArrayError error;
    ArrayType *a = create_array(shape, 2, &error);
    ArrayType *b = create_array(shape, 2, &error);
    ArrayType *result = create_array(shape, 2, &error);
    int passed = a != NULL && b != NULL && result != NULL && error == ARRAY_SUCCESS;

    if (passed) {
        for (size_t i = 0; i < a->size; i++) {
            a->data[i] = (float)i;
            b->data[i] = (float)(i * 2);
        }
        error = add_arrays(result, a, b);
        passed = (error == ARRAY_SUCCESS);
        for (size_t i = 0; i < result->size; i++) {
            passed &= (result->data[i] == a->data[i] + b->data[i]);
        }
    }

    print_test_result("test_add_arrays", passed);
    free_array(a);
    free_array(b);
    free_array(result);
}

// Function to test array multiplication
void test_multiply_arrays() {
    int shape[] = {2, 3};
    ArrayError error;
    ArrayType *a = create_array(shape, 2, &error);
    ArrayType *b = create_array(shape, 2, &error);
    ArrayType *result = create_array(shape, 2, &error);
    int passed = a != NULL && b != NULL && result != NULL && error == ARRAY_SUCCESS;

    if (passed) {
        for (size_t i = 0; i < a->size; i++) {
            a->data[i] = (float)i;
            b->data[i] = (float)(i + 1);
        }
        error = multiply_arrays(result, a, b);
        passed = (error == ARRAY_SUCCESS);
        for (size_t i = 0; i < result->size; i++) {
            passed &= (result->data[i] == a->data[i] * b->data[i]);
        }
    }

    print_test_result("test_multiply_arrays", passed);
    free_array(a);
    free_array(b);
    free_array(result);
}

// Function to test memory pool creation and allocation
void test_memory_pool() {
    size_t pool_size = 1024;
    MemoryPoolType *pool = create_memory_pool(pool_size);
    int passed = pool != NULL;

    if (passed) {
        void *block1 = allocate_from_pool(pool, 256);
        void *block2 = allocate_from_pool(pool, 256);
        passed = block1 != NULL && block2 != NULL &&
                 ((char *)block1 + 256 <= (char *)block2);
    }

    print_test_result("test_memory_pool", passed);
    destroy_memory_pool(pool);
}

int main() {
    test_create_array();
    test_add_arrays();
    test_multiply_arrays();
    test_memory_pool();
    return 0;
}
