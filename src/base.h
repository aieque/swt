#ifndef BASE_H
#define BASE_H

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

typedef uint8_t  u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;

typedef int8_t  i8;
typedef int16_t i16;
typedef int32_t i32;
typedef int64_t i64;

typedef u8 b8;

#define global static
#define internal static
#define local_persist static

inline b8 is_whitespace(char chr) {
    return chr == ' ' || chr == '\t' || chr == '\r' || chr == '\n';
}

#endif