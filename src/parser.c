#include "parser.h"

void parse(TokenList tokenList){
    ASTList AST = CreateASTList(5);


    for(int i = 0; i < tokenList.index; i++){
        TokenList currentLine = CreateTokenList(5);

        for(int j = i; j < tokenList.index; j++){
            if(tokenList.tokens[j].type == NEWLINE){
                i = j;
                break;
            }
            if(j == tokenList.index-1){
                i=tokenList.index-1;
            }
            currentLine = AddToTokenList(currentLine,tokenList.tokens[j]);
        }
        Token* tokens = currentLine.tokens;
		for(int k = 0; k < currentLine.index; k++){
			printf("%s\n",tokens[k].value);
			printf("%d\n",tokens[k].type);
		}
        free(currentLine.tokens);
    }

    DestroyTokenList(tokenList);
    DestroyASTList(AST);
}