// Until we establish a build system, I'll just do a unity build.
#include "utils.cpp"
#include "parser.cpp"
#include "tokenizer.cpp"

#include "base.h"

#include "utils.h"
#include "tokenizer.h"
#include "parser.h"

int main(int argument_count, char **arsguments) {
    printf("swt - static web tools\n");
    
    Tokenizer tokenizer("main.swt");
    Parser parser(&tokenizer);

    parser.parse();

    return 0;
}