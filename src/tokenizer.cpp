#include "tokenizer.h"

void get_token_info(char *dest, Token token) {
    #define ENTRY(type, ...) case TOKEN_##type: sprintf(dest, __VA_ARGS__); break
    
    switch (token.type) {
        ENTRY(INVALID, "Invalid");
        ENTRY(EOF, "End of File");
        ENTRY(IDENTIFIER, "Identifier (%s)", token.string_value);
        ENTRY(HTML_STRING, "Html String (%s)", token.string_value);
        ENTRY(ARROW, "Arrow");
        ENTRY(DOUBLE_COLON, "Double Colon");

        default: {
            sprintf(dest, "'%c' Token", (char)token.type);
        } break;
    };

    #undef ENTRY
}

Tokenizer::Tokenizer(const char *file_path) {
    file = read_entire_file(file_path);
    strcpy(file_name, file_path);

    if (!file) {
        printf("[tokenizer]: unable to open file %s.\n", file_path);
    }

    scratch = create_memory_arena();
}

void Tokenizer::advance(i32 count) {
    while (count--) {
        offset += 1;
        column += 1;

        current_char = file[offset];
        next_char = file[offset + 1];
    }

    if (current_char == '\n') {
        line += 1;
        column = 1;
        line_start = offset + 1;
    }
}

void Tokenizer::skip_whitespace() {
    while (is_whitespace(current_char)) {
        advance();
    }
}

Token Tokenizer::get_token() {
    advance();

    skip_whitespace();

    previous_offset = offset;
    
    Token token = {};

#define SINGLE_CHAR(chr) case chr: {token.type = (Token_Type)chr;} break;

    switch (current_char) {
        case '\0': {
            token.type = TOKEN_EOF;
        } break;

        SINGLE_CHAR('(');
        SINGLE_CHAR(')');
        SINGLE_CHAR('{');
        SINGLE_CHAR('}');
        SINGLE_CHAR(';');

        case '`': {
            i32 string_start = offset + 1;
            
            // Read unitl next `
            // TODO: Check for EOF, since that would otherwise lead to a crash.
            do { advance(); } while (current_char != '`');

            i32 string_end = offset;
            i32 string_length = string_end - string_start;

            char *content = (char *)scratch.alloc(string_length + 1);

            memcpy(content, file + string_start, string_length);
            content[string_length] = 0;

            token.string_value = content;
            token.type = TOKEN_HTML_STRING;
        } break;

        case '-': {
            if (next_char == '>') {
                token.type = TOKEN_ARROW;
                advance(1);
            }
        } break;

        case ':': {
            if (next_char == ':') {
                token.type = TOKEN_DOUBLE_COLON;
                advance(1);
            }
        } break;

        default: {
            // @TODO Numbers
            i32 string_start = offset;
            
            while (!is_whitespace(current_char)) {
                advance();
            }

            i32 string_end = offset;
            i32 string_length = string_end - string_start;

            char *content = (char *)scratch.alloc(string_length + 1);

            memcpy(content, file + string_start, string_length);
            content[string_length] = 0;

            token.string_value = content;
            token.type = TOKEN_IDENTIFIER;
        };
    }

    return token;
}