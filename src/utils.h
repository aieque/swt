#ifndef UTILS_H
#define UTILS_H

#include "base.h"

char *read_entire_file(const char *file_path);

struct Memory_Arena {
    u8 *base;
    i32 size;
    i32 used;

    void *alloc(i32 size);
};

Memory_Arena create_memory_arena(i32 size = 4096);
void release_memory_arena(Memory_Arena *arena);

#endif