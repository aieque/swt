#include "parser.h"

Parser::Parser(Tokenizer *tokenizer) {
    this->tokenizer = tokenizer;
}

void Parser::error(const char *message) {
    printf("[parser]: In file %s (line %i, column %i):\n",
        tokenizer->file_name, tokenizer->line, tokenizer->column);

    char line_buffer[256];
    i32 buffer_offset = 0;

    for (char *chr = tokenizer->file + tokenizer->line_start; *chr != '\n'; ++chr) {
        line_buffer[buffer_offset++] = *chr;
    }

    line_buffer[buffer_offset] = 0;

    printf("\n%s\n", line_buffer);

    for (buffer_offset = 0; buffer_offset < tokenizer->previous_offset - tokenizer->line_start; ++buffer_offset) {
        line_buffer[buffer_offset] = '~';
    }

    line_buffer[buffer_offset] = '^';
    line_buffer[buffer_offset + 1] = 0;

    printf("%s\n", line_buffer);
    printf("%s\n\n", message);

}

void Parser::parse() {
    token = tokenizer->get_token();

    // When parsing from the root level, we expect only declaration, imports etc.
    // Since multiple files are weeks away, we'll only be dealing with declarations.
    // Therefore if an identifier does not match with the declaration syntax:
    // NAME :: VALUE (we use '()' to distinguish between procs and constants)
    // the program will just throw an error.

    if (token.type == TOKEN_IDENTIFIER) {
        token = tokenizer->get_token();
        
        if (token.type == TOKEN_DOUBLE_COLON) {
            token = tokenizer->get_token();

            if (token.type == '(') {
                parse_proc();
            }
        }
    }
}

void Parser::parse_proc() {
    // @TODO Parse arguments.

    token = tokenizer->get_token();
    if (token.type != ')') {
        error("We don't currently support arguments...\n");
        return;
    }

    // @TODO Parse return type
    // Right now we just assume that it's an html string.

    token = tokenizer->get_token();
    if (token.type != '{') {

    }
}