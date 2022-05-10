#include "token.h"



TokenList CreateTokenList(int size){
    TokenList list;
    list.size = size;
    list.index = 0;
    list.tokens = (Token*) malloc((size) * sizeof(Token));
    return list;
}


TokenList AddToTokenList(TokenList tokenList,Token token){
    if(tokenList.size <= tokenList.index){
        tokenList.size += 128;
        Token* temp = realloc(tokenList.tokens,sizeof(Token)*(tokenList.size));
        if(temp == NULL){
            puts("Failed To Allocate Memory!");
            exit(-1);
        }
        tokenList.tokens = temp;
    }
    tokenList.tokens[tokenList.index] = token;
    tokenList.index+=1;
    return tokenList;
}


void DestroyTokenList(TokenList tokenList){
    free(tokenList.tokens);
}