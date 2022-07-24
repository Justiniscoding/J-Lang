#ifndef JLANG_TOKEN
#define JLANG_TOKEN
#include <stdlib.h>
#include <stdio.h>
enum _TokenType{
    SEMICOLON,
    NUMBER,
    STRING,
    ARROW,
    IDENTIFIER,
    WHITESPACE,
    NEWLINE,
    RIGHTPARAM,
    LEFTPARAM,
    RIGHTCURLY,
    LEFTCURLY,
    COMMA,
    PLUS,
    MINUS,
    EQUALS,
	GREATER_THAN,
	SMALLER_THAN,
    TOKEN_AMOUNT
};
typedef enum _TokenType TokenType;
struct _Token{
    TokenType type;
    char* value;
    int line;
};
typedef struct _Token Token;

struct _TokenList{
    Token* tokens;
    int size;
    int index;
};
typedef struct _TokenList TokenList;
TokenList CreateTokenList(int size);
TokenList AddToTokenList(TokenList tokenList,Token token);
void DestroyTokenList(TokenList tokenList);
#endif