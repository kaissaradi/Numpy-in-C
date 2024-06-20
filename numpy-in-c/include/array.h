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
ArrayType* create_array(int *shape, int ndim, ArrayError *error);
void free_array(ArrayType *arr);
ArrayError add_arrays(ArrayType *result, const ArrayType *a, const ArrayType *b);
ArrayError multiply_arrays(ArrayType *result, const ArrayType *a, const ArrayType *b);

#endif // ARRAY_H