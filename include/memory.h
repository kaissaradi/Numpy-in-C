#ifndef MEMORY_H
#define MEMORY_H

#include <stddef.h>

// Define an enum for memory error codes
typedef enum {
    MEMORY_SUCCESS = 0,
    MEMORY_ERROR_NULL_POINTER,
    MEMORY_ERROR_ALLOCATION_FAILED,
    MEMORY_ERROR_OUT_OF_MEMORY,
    // Add more error codes as needed
} MemoryError;

// Define a type for the memory pool
typedef struct {
    void *start;
    void *current;
    size_t size;
    size_t used;
} MemoryPoolType;

// Function prototypes for memory management

/**
 * @brief Creates a memory pool of the specified size.
 *
 * @param size The size of the memory pool to create.
 * @return Pointer to the newly created memory pool, or NULL if an error occurred.
 */
MemoryPoolType* create_memory_pool(size_t size);

/**
 * @brief Allocates memory from the memory pool.
 *
 * @param pool Pointer to the memory pool.
 * @param size The size of the memory to allocate.
 * @return Pointer to the allocated memory, or NULL if an error occurred.
 */
void* allocate_from_pool(MemoryPoolType* pool, size_t size);

/**
 * @brief Destroys the memory pool and frees all associated memory.
 *
 * @param pool Pointer to the memory pool to destroy.
 */
void destroy_memory_pool(MemoryPoolType* pool);

#endif // MEMORY_H
