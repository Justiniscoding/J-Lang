#ifndef JLANG_LEXER
#define JLANG_LEXER
#include <string.h>
#include <stdbool.h>
#include "regex.h"
#include "string.h"
#include "token.h"
TokenList lex(char* code);
#endif