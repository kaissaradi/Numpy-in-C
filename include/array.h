#ifndef ARRAY_H
#define ARRAY_H

#include <stddef.h>

// Define an enum for error codes
typedef enum {
    ARRAY_SUCCESS = 0,
    ARRAY_ERROR_NULL_POINTER,
    ARRAY_ERROR_INVALID_DIMENSION,
    ARRAY_ERROR_MEMORY_ALLOCATION,
    // Add more error codes as needed
} ArrayError;

// Define a type for the array structure
typedef struct {
    float *data;
    int *shape;
    int ndim;
    size_t size;
    size_t itemsize;
} ArrayType;

// Function prototypes for array operations

/**
 * Creates a new array with the given shape and number of dimensions.
 * 
 * @param shape Array containing the size of each dimension.
 * @param ndim Number of dimensions.
 * @param error Pointer to an error code variable.
 * @return Pointer to the newly created array or NULL if an error occurred.
 */
ArrayType* create_array(const int *shape, int ndim, ArrayError *error);

/**
 * Frees the memory allocated for an array.
 * 
 * @param arr Pointer to the array to be freed.
 */
void free_array(ArrayType *arr);

/**
 * Adds two arrays element-wise and stores the result in a third array.
 * 
 * @param result Pointer to the array where the result will be stored.
 * @param a Pointer to the first array.
 * @param b Pointer to the second array.
 * @return Error code indicating success or failure.
 */
ArrayError add_arrays(ArrayType *result, const ArrayType *a, const ArrayType *b);

/**
 * Multiplies two arrays element-wise and stores the result in a third array.
 * 
 * @param result Pointer to the array where the result will be stored.
 * @param a Pointer to the first array.
 * @param b Pointer to the second array.
 * @return Error code indicating success or failure.
 */
ArrayError multiply_arrays(ArrayType *result, const ArrayType *a, const ArrayType *b);

#endif // ARRAY_H
