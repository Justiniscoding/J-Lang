#include "ast.h"


ASTList CreateASTList(int size){
    ASTList list;
    list.size = size;
    list.index = 0;
    list.astNodes = (ASTNode*) malloc(size * sizeof(ASTNode));
    return list;
}


ASTList AddToASTList(ASTList list,ASTNode node){
    if(list.size <= list.index){
        list.size += 128;
        ASTNode* temp = realloc(list.astNodes,sizeof(ASTNode)*(list.size));
        if(temp == NULL){
            puts("Failed To Allocate Memory!");
            exit(-1);
        }
        list.astNodes = temp;
        free(temp);
    }
    list.astNodes[list.index] = node;
    list.index+=1;
    return list;
}


void DestroyASTList(ASTList list){
    free(list.astNodes);
}