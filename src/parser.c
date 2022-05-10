#include "parser.h"

void parse(TokenList tokenList){
    ASTList AST = CreateASTList(5);

    for(int i = 0; i < tokenList.index; i++){
        printf("Value: %s\n",tokenList.tokens[i].value);
    }

    // for(int i = 0; i < tokenList.index; i++){
    //     TokenList currentLine = CreateTokenList(5);

    //     for(int j = i; j < tokenList.index; j++){
    //         if(tokenList.tokens[j].type == NEWLINE){
    //             i = j;
    //             break;
    //         }
    //         if(j == tokenList.index-1){
    //             i=tokenList.index-1;
    //         }
    //         currentLine = AddToTokenList(currentLine,tokenList.tokens[j]);
    //     }
    //     for(int j = 0; j < currentLine.index; j++){
    //         printf("Value: %s\n",currentLine.tokens[j].value);
    //     }
    //     printf("End Expression\n");

    //     Token* tokens = currentLine.tokens;
    //     if(tokens[0].type == IDENTIFIER && tokens[1].type == ARROW && tokens[2].type == STRING && tokens[3].type == SEMICOLON){
    //         puts("YAY");
    //     }
    //     free(currentLine.tokens);
    // }

    DestroyTokenList(tokenList);
    DestroyASTList(AST);
}