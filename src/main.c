#include <stdlib.h>
#include <stdio.h>
#include "file.h"
#include "parser.h"
#include "lexer.h"
#include "regex.h"
#include "string.h"
#define JLANG_V "1.00"

TokenList tokens;


int main(int argc, char* argv[]) {
    char *file = argv[1];
    char *fileContents = fileRead(file);
    if(!fileContents){
        return -1;
    }
    parse(lex(fileContents));
    return 0;
}