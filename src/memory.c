#include "memory.h"
#include <stdlib.h>

MemoryPoolType* create_memory_pool(size_t size) {
    MemoryPoolType *pool = (MemoryPoolType*)malloc(sizeof(MemoryPoolType));
    if (!pool) return NULL;

    pool->start = malloc(size);
    if (!pool->start) {
        free(pool);
        return NULL;
    }

    pool->current = pool->start;
    pool->size = size;
    pool->used = 0;
    return pool;
}

void* allocate_from_pool(MemoryPoolType* pool, size_t size) {
    if (pool->used + size > pool->size) return NULL; // Out of memory
    void *ptr = pool->current;
    pool->current = (char*)pool->current + size;
    pool->used += size;
    return ptr;
}

void destroy_memory_pool(MemoryPoolType* pool) {
    if (pool) {
        free(pool->start);
        free(pool);
    }
}
