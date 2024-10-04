#include <stdio.h>
#include <stdlib.h>
#include "array.h"

void print_test_result(const char *test_name, int passed, const char *details) {
    printf("[%s] %s: %s\n", passed ? "PASS" : "FAIL", test_name, details);
}

void test_create_array() {
    int shape[] = {2, 3};
    ArrayError error;
    ArrayType *arr = create_array(shape, 2, &error);
    int passed = (arr != NULL && error == ARRAY_SUCCESS);
    char details[256];

    if (passed) {
        snprintf(details, sizeof(details), "Array created with shape [%d, %d]", shape[0], shape[1]);
    } else {
        snprintf(details, sizeof(details), "Failed to create array");
    }

    print_test_result("test_create_array", passed, details);
    free_array(arr);
}

void test_add_arrays() {
    int shape_a[] = {2, 1};
    int shape_b[] = {1, 3};
    ArrayError error;
    char details[256];

    ArrayType *a = create_array(shape_a, 2, &error);
    ArrayType *b = create_array(shape_b, 2, &error);
    ArrayType *result = NULL;
    int passed = a != NULL && b != NULL && error == ARRAY_SUCCESS;

    if (!passed) {
        printf("Error creating arrays for addition: %d\n", error);
        return;
    }

    // Initialize arrays
    for (size_t i = 0; i < a->size; i++) {
        a->data[i] = (float)i + 1;  // Initialize 'a' with [1, 2]
    }
    for (size_t i = 0; i < b->size; i++) {
        b->data[i] = (float)(i + 1) * 2;  // Initialize 'b' with [2, 4, 6]
    }

    // Perform addition
    error = add_arrays(&result, a, b);
    passed = (error == ARRAY_SUCCESS);

    // Manually broadcast 'b' to match the shape of 'a'
    ArrayType *b_broadcasted = create_array(shape_a, 2, &error);
    for (size_t i = 0; i < b_broadcasted->size; i++) {
        b_broadcasted->data[i] = b->data[i % b->size];
    }

    // Compare result with expected values
    for (size_t i = 0; i < result->size; i++) {
        passed &= (result->data[i] == a->data[i] + b_broadcasted->data[i]);
    }

    free_array(b_broadcasted);

    snprintf(details, sizeof(details), "Addition result array - Size: %zu", result->size);
    print_test_result("test_add_arrays", passed, details);

    free_array(a);
    free_array(b);
    free_array(result);
}

void test_multiply_arrays() {
    int shape_a[] = {2, 1};
    int shape_b[] = {1, 3};
    ArrayError error;
    char details[256];

    ArrayType *a = create_array(shape_a, 2, &error);
    ArrayType *b = create_array(shape_b, 2, &error);
    ArrayType *result = NULL;
    int passed = a != NULL && b != NULL && error == ARRAY_SUCCESS;

    if (!passed) {
        printf("Error creating arrays for multiplication: %d\n", error);
        return;
    }

    // Initialize arrays
    for (size_t i = 0; i < a->size; i++) {
        a->data[i] = (float)i + 1;  // Initialize 'a' with [1, 2]
    }
    for (size_t i = 0; i < b->size; i++) {
        b->data[i] = (float)(i + 1) * 2;  // Initialize 'b' with [2, 4, 6]
    }

    // Perform multiplication
    error = multiply_arrays(&result, a, b);
    passed = (error == ARRAY_SUCCESS);

    // Manually broadcast 'b' to match the shape of 'a'
    ArrayType *b_broadcasted = create_array(shape_a, 2, &error);
    for (size_t i = 0; i < b_broadcasted->size; i++) {
        b_broadcasted->data[i] = b->data[i % b->size];
    }

    // Compare result with expected values
    for (size_t i = 0; i < result->size; i++) {
        passed &= (result->data[i] == a->data[i] * b_broadcasted->data[i]);
    }

    free_array(b_broadcasted);

    snprintf(details, sizeof(details), "Multiplication result array - Size: %zu", result->size);
    print_test_result("test_multiply_arrays", passed, details);

    free_array(a);
    free_array(b);
    free_array(result);
}

void test_broadcast_simple() {
    int shape_a[] = {2, 1};
    int shape_b[] = {2, 3};
    ArrayError error;
    char details[256];

    ArrayType *a = create_array(shape_a, 2, &error);
    ArrayType *b = create_array(shape_b, 2, &error);
    ArrayType *result = NULL;
    int passed = a != NULL && b != NULL && error == ARRAY_SUCCESS;

    if (!passed) {
        printf("Error creating arrays for simple broadcast: %d\n", error);
        return;
    }

    // Initialize arrays
    for (size_t i = 0; i < a->size; i++) {
        a->data[i] = (float)i + 1;  // Initialize 'a' with [1, 2]
    }
    for (size_t i = 0; i < b->size; i++) {
        b->data[i] = (float)(i + 1);  // Initialize 'b' with [1, 2, 3, 4, 5, 6]
    }

    // Perform addition
    error = add_arrays(&result, a, b);
    passed = (error == ARRAY_SUCCESS);

    // Manually broadcast 'a' to match the shape of 'b'
    ArrayType *a_broadcasted = create_array(shape_b, 2, &error);
    for (size_t i = 0; i < a_broadcasted->size; i++) {
        a_broadcasted->data[i] = a->data[i / b->shape[1]];
    }

    // Compare result with expected values
    for (size_t i = 0; i < result->size; i++) {
        passed &= (result->data[i] == a_broadcasted->data[i] + b->data[i]);
    }

    free_array(a_broadcasted);

    snprintf(details, sizeof(details), "Simple broadcast result array - Size: %zu", result->size);
    print_test_result("test_broadcast_simple", passed, details);

    free_array(a);
    free_array(b);
    free_array(result);
}

void test_broadcast_different_dimensions() {
    int shape_a[] = {2, 1, 3};
    int shape_b[] = {1, 3};
    ArrayError error;
    char details[256];

    ArrayType *a = create_array(shape_a, 3, &error);
    ArrayType *b = create_array(shape_b, 2, &error);
    ArrayType *result = NULL;
    int passed = a != NULL && b != NULL && error == ARRAY_SUCCESS;

    if (!passed) {
        printf("Error creating arrays for different dimensions broadcast: %d\n", error);
        return;
    }

    // Initialize arrays
    for (size_t i = 0; i < a->size; i++) {
        a->data[i] = (float)(i + 1);  // Initialize 'a' with increasing values
    }
    for (size_t i = 0; i < b->size; i++) {
        b->data[i] = (float)(i + 1);  // Initialize 'b' with [1, 2, 3]
    }

    // Perform addition
    error = add_arrays(&result, a, b);
    passed = (error == ARRAY_SUCCESS);

    // Manually broadcast 'b' to match the shape of 'a'
    ArrayType *b_broadcasted = create_array(shape_a, 3, &error);
    for (size_t i = 0; i < b_broadcasted->size; i++) {
        b_broadcasted->data[i] = b->data[i % b->size];
    }

    // Compare result with expected values
    for (size_t i = 0; i < result->size; i++) {
        passed &= (result->data[i] == a->data[i] + b_broadcasted->data[i]);
    }

    free_array(b_broadcasted);

    snprintf(details, sizeof(details), "Different dimensions broadcast result array - Size: %zu", result->size);
    print_test_result("test_broadcast_different_dimensions", passed, details);

    free_array(a);
    free_array(b);
    free_array(result);
}

void test_broadcast_scalar() {
    int shape_a[] = {};
    int shape_b[] = {2, 3};
    ArrayError error;
    char details[256];

    ArrayType *a = create_array(shape_a, 0, &error);
    ArrayType *b = create_array(shape_b, 2, &error);
    ArrayType *result = NULL;
    int passed = a != NULL && b != NULL && error == ARRAY_SUCCESS;

    if (!passed) {
        printf("Error creating arrays for scalar broadcast: %d\n", error);
        return;
    }

    // Initialize arrays
    a->data[0] = 2.0;  // Initialize 'a' as scalar [2]
    for (size_t i = 0; i < b->size; i++) {
        b->data[i] = (float)(i + 1);  // Initialize 'b' with [1, 2, 3, 4, 5, 6]
    }

    // Perform multiplication
    error = multiply_arrays(&result, a, b);
    passed = (error == ARRAY_SUCCESS);

    // Manually broadcast 'a' to match the shape of 'b'
    ArrayType *a_broadcasted = create_array(shape_b, 2, &error);
    for (size_t i = 0; i < a_broadcasted->size; i++) {
        a_broadcasted->data[i] = a->data[0];
    }

    // Compare result with expected values
    for (size_t i = 0; i < result->size; i++) {
        passed &= (result->data[i] == a_broadcasted->data[i] * b->data[i]);
    }

    free_array(a_broadcasted);

    snprintf(details, sizeof(details), "Scalar broadcast result array - Size: %zu", result->size);
    print_test_result("test_broadcast_scalar", passed, details);

    free_array(a);
    free_array(b);
    free_array(result);
}

// Main function to run all tests
int main() {
    test_create_array();
    test_add_arrays();
    test_multiply_arrays();
    test_broadcast_simple();
    test_broadcast_different_dimensions();
    test_broadcast_scalar();
    return 0;
}
