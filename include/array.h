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
    int *strides;
    int ndim;
    size_t size;
    size_t itemsize;
} ArrayType;

// Define a type for shape information
typedef struct {
    int *shape;
    int ndim;
} ShapeInfo;

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

/**
 * Compares the shapes of two arrays and determines the broadcast shape.
 * 
 * @param a Pointer to the first array.
 * @param b Pointer to the second array.
 * @return Pointer to a ShapeInfo struct containing the broadcast shape or NULL if the shapes are not compatible.
 */
ShapeInfo* compare_shapes(const ArrayType *a, const ArrayType *b);

/**
 * Calculates the linear index from multidimensional indices.
 * 
 * @param indices Array of indices.
 * @param shape Array of shape dimensions.
 * @param strides Array of strides.
 * @param ndim Number of dimensions.
 * @return Linear index.
 */
size_t calculate_index(const int *indices, const int *shape, const int *strides, int ndim);

#endif // ARRAY_H
