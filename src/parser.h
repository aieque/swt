#ifndef PARSER_H
#define PARSER_H

#include "base.h"

#include "tokenizer.h"

struct Ast_Node {

};

struct Parser {
    Tokenizer *tokenizer;
    Token token;

    Ast_Node *root;

    Parser(Tokenizer *tokenizer);

    void error(const char *message);    

    // @TODO Add arguments to the parse function.
    void parse();

    void parse_proc();
};

#endif