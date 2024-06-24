#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <float.h>
#include <limits.h>
#include "array.h"
#include "memory.h"

// Helper function to print test results with details
void print_test_result(const char *test_name, int result, const char *details) {
    printf("%s: %s (%s)\n", test_name, result ? "PASSED" : "FAILED", details);
}

// Function to test array creation
void test_create_array() {
    ArrayError error;
    char details[256];

    // Test 1D array
    int shape1[] = {5};
    ArrayType *arr1 = create_array(shape1, 1, &error);
    if (arr1 == NULL) {
        printf("Error creating 1D array: %d\n", error);
        return;
    }
    int passed1 = arr1->ndim == 1 && arr1->size == 5;
    snprintf(details, sizeof(details), "1D array - Size: %zu, Dimensions: %d", arr1->size, arr1->ndim);
    print_test_result("test_create_array (1D)", passed1, details);
    free_array(arr1);

    // Test 2D array
    int shape2[] = {2, 3};
    ArrayType *arr2 = create_array(shape2, 2, &error);
    if (arr2 == NULL) {
        printf("Error creating 2D array: %d\n", error);
        return;
    }
    int passed2 = arr2->ndim == 2 && arr2->size == 6;
    snprintf(details, sizeof(details), "2D array - Size: %zu, Dimensions: %d", arr2->size, arr2->ndim);
    print_test_result("test_create_array (2D)", passed2, details);
    free_array(arr2);

    // Test invalid array creation
    ArrayType *arr3 = create_array(NULL, 2, &error);
    int passed3 = arr3 == NULL && error == ARRAY_ERROR_INVALID_DIMENSION;
    snprintf(details, sizeof(details), "Invalid array creation (NULL shape)");
    print_test_result("test_create_invalid_array (NULL shape)", passed3, details);
}

// Function to test array addition
void test_add_arrays() {
    int shape[] = {2, 3};
    ArrayError error;
    char details[256];

    ArrayType *a = create_array(shape, 2, &error);
    ArrayType *b = create_array(shape, 2, &error);
    ArrayType *result = create_array(shape, 2, &error);
    int passed = a != NULL && b != NULL && result != NULL && error == ARRAY_SUCCESS;

    if (!passed) {
        printf("Error creating arrays for addition: %d\n", error);
        return;
    }

    // Initialize arrays
    for (size_t i = 0; i < a->size; i++) {
        a->data[i] = (float)i;
        b->data[i] = (float)(i * 2);
    }

    // Perform addition
    error = add_arrays(result, a, b);
    passed = (error == ARRAY_SUCCESS);
    for (size_t i = 0; i < result->size; i++) {
        passed &= (result->data[i] == a->data[i] + b->data[i]);
    }
    snprintf(details, sizeof(details), "Addition result array - Size: %zu", result->size);
    print_test_result("test_add_arrays", passed, details);

    free_array(a);
    free_array(b);
    free_array(result);
}

// Function to test array addition with invalid dimensions
void test_add_invalid_arrays() {
    int shape1[] = {2, 3};
    int shape2[] = {3, 2};
    ArrayError error;
    char details[256];

    ArrayType *a = create_array(shape1, 2, &error);
    ArrayType *b = create_array(shape2, 2, &error);
    ArrayType *result = create_array(shape1, 2, &error);
    int passed = a != NULL && b != NULL && result != NULL && error == ARRAY_SUCCESS;

    if (passed) {
        error = add_arrays(result, a, b);
        passed = (error == ARRAY_ERROR_INVALID_DIMENSION);
    }

    snprintf(details, sizeof(details), "Addition with invalid dimensions");
    print_test_result("test_add_invalid_arrays", passed, details);
    free_array(a);
    free_array(b);
    free_array(result);
}

// Function to test array multiplication
void test_multiply_arrays() {
    int shape[] = {2, 3};
    ArrayError error;
    char details[256];

    ArrayType *a = create_array(shape, 2, &error);
    ArrayType *b = create_array(shape, 2, &error);
    ArrayType *result = create_array(shape, 2, &error);
    int passed = a != NULL && b != NULL && result != NULL && error == ARRAY_SUCCESS;

    if (!passed) {
        printf("Error creating arrays for multiplication: %d\n", error);
        return;
    }

    // Initialize arrays
    for (size_t i = 0; i < a->size; i++) {
        a->data[i] = (float)i;
        b->data[i] = (float)(i + 1);
    }

    // Perform multiplication
    error = multiply_arrays(result, a, b);
    passed = (error == ARRAY_SUCCESS);
    for (size_t i = 0; i < result->size; i++) {
        passed &= (result->data[i] == a->data[i] * b->data[i]);
    }
    snprintf(details, sizeof(details), "Multiplication result array - Size: %zu", result->size);
    print_test_result("test_multiply_arrays", passed, details);

    free_array(a);
    free_array(b);
    free_array(result);
}

// Function to test array multiplication with invalid dimensions
void test_multiply_invalid_arrays() {
    int shape1[] = {2, 3};
    int shape2[] = {3, 2};
    ArrayError error;
    char details[256];

    ArrayType *a = create_array(shape1, 2, &error);
    ArrayType *b = create_array(shape2, 2, &error);
    ArrayType *result = create_array(shape1, 2, &error);
    int passed = a != NULL && b != NULL && result != NULL && error == ARRAY_SUCCESS;

    if (passed) {
        error = multiply_arrays(result, a, b);
        passed = (error == ARRAY_ERROR_INVALID_DIMENSION);
    }

    snprintf(details, sizeof(details), "Multiplication with invalid dimensions");
    print_test_result("test_multiply_invalid_arrays", passed, details);
    free_array(a);
    free_array(b);
    free_array(result);
}

// Function to test memory pool creation and allocation
void test_memory_pool() {
    size_t pool_size = 1024;
    MemoryPoolType *pool = create_memory_pool(pool_size);
    int passed = pool != NULL;
    char details[256];

    if (!passed) {
        printf("Error creating memory pool\n");
        return;
    }

    void *block1 = allocate_from_pool(pool, 256);
    void *block2 = allocate_from_pool(pool, 256);
    passed = block1 != NULL && block2 != NULL && ((char *)block1 + 256 <= (char *)block2);

    snprintf(details, sizeof(details), "Memory pool - Blocks allocated: %s, %s", 
             block1 != NULL ? "Yes" : "No", block2 != NULL ? "Yes" : "No");
    print_test_result("test_memory_pool", passed, details);

    destroy_memory_pool(pool);
}

// Function to test memory pool allocation exceeding pool size
void test_memory_pool_exceed() {
    size_t pool_size = 512;
    MemoryPoolType *pool = create_memory_pool(pool_size);
    int passed = pool != NULL;
    char details[256];

    if (!passed) {
        printf("Error creating memory pool\n");
        return;
    }

    void *block1 = allocate_from_pool(pool, 256);
    void *block2 = allocate_from_pool(pool, 256);
    void *block3 = allocate_from_pool(pool, 256); // This should fail
    passed = block1 != NULL && block2 != NULL && block3 == NULL;

    snprintf(details, sizeof(details), "Memory pool exceed - Blocks allocated: %s, %s, %s", 
             block1 != NULL ? "Yes" : "No", block2 != NULL ? "Yes" : "No", block3 != NULL ? "No" : "Yes");
    print_test_result("test_memory_pool_exceed", passed, details);

    destroy_memory_pool(pool);
}

// Main function to run all tests
int main() {
    test_create_array();
    test_add_arrays();
    test_add_invalid_arrays();
    test_multiply_arrays();
    test_multiply_invalid_arrays();
    test_memory_pool();
    test_memory_pool_exceed();
    return 0;
}
