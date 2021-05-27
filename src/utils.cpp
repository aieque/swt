#include "utils.h"

char *read_entire_file(const char *file_path) {
    FILE *fp = fopen(file_path, "rb");

    if (!fp) return NULL;

    fseek(fp, 0L, SEEK_END);
    i32 size = ftell(fp);
    rewind(fp);

    char *file_data = (char *)malloc(size + 1);
    fread(file_data, size, 1, fp);

    fclose(fp);

    file_data[size] = 0;

    return file_data;
}

void *Memory_Arena::alloc(i32 size) {
    void *result = base + used;
    used += size;

    return result;
}

Memory_Arena create_memory_arena(i32 size) {
    Memory_Arena arena = {};
    
    arena.base = (u8 *)malloc(size);
    arena.size = size;

    return arena;
}

void release_memory_arena(Memory_Arena *arena) {
    free(arena->base);
}