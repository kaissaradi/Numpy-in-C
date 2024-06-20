#ifndef MEMORY_H
#define MEMORY_H

#include <stddef.h>

// Define a type for the memory pool
typedef struct {
    void *start;
    void *current;
    size_t size;
    size_t used;
} MemoryPoolType;

// Function prototypes for memory management
MemoryPoolType* create_memory_pool(size_t size);
void* allocate_from_pool(MemoryPoolType* pool, size_t size);
void destroy_memory_pool(MemoryPoolType* pool);

#define HANDLE_ERROR(msg) \
    do { perror(msg); exit(EXIT_FAILURE); } while (0)

#endif // MEMORY_H
