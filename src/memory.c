#include "memory.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

// Create a memory pool of the specified size
MemoryPoolType* create_memory_pool(size_t size) {
    MemoryPoolType *pool = (MemoryPoolType*)malloc(sizeof(MemoryPoolType));
    if (!pool) {
        fprintf(stderr, "Failed to allocate memory for memory pool structure\n");
        return NULL;
    }

    pool->start = malloc(size);
    if (!pool->start) {
        free(pool);
        fprintf(stderr, "Failed to allocate memory for memory pool\n");
        return NULL;
    }

    pool->current = pool->start;
    pool->size = size;
    pool->used = 0;
    return pool;
}

// Allocate memory from the memory pool
void* allocate_from_pool(MemoryPoolType* pool, size_t size) {
    if (!pool || !pool->start) {
        fprintf(stderr, "Memory pool is not initialized\n");
        return NULL;
    }

    if (pool->used + size > pool->size) {
        fprintf(stderr, "Not enough memory in the pool\n");
        return NULL;
    }

    void *ptr = pool->current;
    pool->current = (char*)pool->current + size;
    pool->used += size;
    return ptr;
}

// Destroy the memory pool and free all associated memory
void destroy_memory_pool(MemoryPoolType* pool) {
    if (pool) {
        free(pool->start);
        free(pool);
    }
}
