#ifndef TOKENIZER_H
#define TOKENIZER_H

#include "base.h"
#include "utils.h"

enum Token_Type : u16 {
    TOKEN_INVALID = 256,

    TOKEN_EOF,

    TOKEN_IDENTIFIER,
    TOKEN_HTML_STRING,
    TOKEN_ARROW,
    TOKEN_DOUBLE_COLON
};

void get_token_info(char *dest, Token_Type type);

struct Token {
    Token_Type type;
    
    union {
        char *string_value;
        i32 integer_value;
        char char_value;
    };
};

struct Tokenizer {
    char *file;
    char file_name[32];

    // Since get_token calls advance the first thing it does, we avoid
    // any mismatched offsets by simply setting it to -1.
    i32 offset = -1;
    i32 line = 1, column = 1;
    
    i32 line_start = 0;
    i32 previous_offset = -1;

    Memory_Arena scratch;

    char current_char, next_char;

    Tokenizer(const char *file_path);

    void advance(i32 count = 1);
    void skip_whitespace();

    Token get_token();
};

#endif