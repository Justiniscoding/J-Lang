#ifndef JLANG_AST
#define JLANG_AST
#include <stdlib.h>
#include <stdio.h>

enum _ASTType{
    FUNCTION_CALL,
    FUNCTION_DEFINE,
    VARIABLE_DEFINE,
    STATEMENT,
    MATH
};
typedef enum _ASTType ASTType;
typedef struct _ASTNode ASTNode;
typedef struct _ASTList ASTList;

struct _ASTNode{
    ASTType type;
    ASTList* children;
};

struct _ASTList{
    ASTNode* astNodes;
    int size;
    int index;
};


ASTList CreateASTList(int size);
ASTList AddToASTList(ASTList tokenList,ASTNode ast);
void DestroyASTList(ASTList list);

#endif