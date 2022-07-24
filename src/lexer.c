#include "lexer.h"
const int tokenAmount = TOKEN_AMOUNT;
Token lexerTokens[tokenAmount] = {
    {
        RIGHTPARAM,
        "("
    },
    {
        LEFTPARAM,
        ")"
    },
    {
        IDENTIFIER,
        "[a-zA-Z][a-zA-Z0-9]*"
    },
    {
        ARROW,
        "->"
    },
	{
		GREATER_THAN,
		">"
	},
	{
		SMALLER_THAN,
		"<"
	},
    {
        NUMBER,
        "[0-9]*"
    },
    {
        SEMICOLON,
        ";"
    },
    {
        COMMA,
        "[,]"
    },
    {
        PLUS,
        "+"
    },
    {
        MINUS,
        "[-]"
    },
    {
        EQUALS,
        "="
    },
    {
        RIGHTCURLY,
        "{"
    },
    {
        LEFTCURLY,
        "{"
    },
    {
        NEWLINE,
        "\n"
    },
    {
        WHITESPACE,
        "[ ]*"
    },
    {
        STRING,
        "\"[^\"]*\""
    }
};
TokenList lex(char* code){
    const int codeLen = strlen(code);
    int startPos = 0;
    int line = 0;
    TokenList tokenList = CreateTokenList(5);
    bool exitLoop = false;
    for(int _ = 0; _ < codeLen; _++){
        for(int i = 0; i < codeLen-_; i++){
            if(exitLoop == true){
                exitLoop = false;
                break;
            }
            for(int j = 0; j < tokenAmount; j++){
                Token token = lexerTokens[j];
                char* codeSnippet = malloc((startPos+i) * sizeof(char));
                strcpy(codeSnippet,slice(code,startPos,startPos+i));
                if(strcmp(codeSnippet,"") == 0){
                    break;
                }
                int result = regexTest(token.value,codeSnippet);
                if(result == 1){
                    if(token.type == NEWLINE){
                        line++;
                    }
                    if(token.type == IDENTIFIER){
                        int tempi = i;
                        codeSnippet = realloc(codeSnippet, ((tempi+1) * sizeof(char)));
                        while(true){
                            tempi++;
                            codeSnippet = realloc(codeSnippet,sizeof(char)*(tempi+1));
                            strcpy(codeSnippet,slice(code,startPos,startPos+tempi));
                            result = regexTest(token.value,codeSnippet);
                            if(result == -1){

                                strcpy(codeSnippet,slice(codeSnippet,0,-2));
                                i=tempi-1;
                                break;
                            }
                        }
                    }
					if(token.type == MINUS){
						int arrowIndex = 0;
						for(int k = 0; k < tokenAmount; k++){
							if(lexerTokens[k].type == ARROW){
								arrowIndex = k;
							}
						}
						codeSnippet = realloc(codeSnippet,sizeof(char)*(i+1));
						strcpy(codeSnippet,slice(code,startPos,startPos+i+1));
						if(regexTest("->",codeSnippet) == 1){
							token = lexerTokens[arrowIndex];
						}else{
							codeSnippet = realloc(codeSnippet,sizeof(char)*(i));
							strcpy(codeSnippet,slice(code,startPos,startPos+i));
						}
					}
                    int tempi = i;
                    char* oldSnippet = codeSnippet;
                    codeSnippet = realloc(codeSnippet, ((tempi+1) * sizeof(char)));
                    bool looping = true;
                    while(true){
                        tempi++;
                        if(tempi > codeLen){
                            strcpy(codeSnippet,oldSnippet);
                            break;
                        }
                        codeSnippet = realloc(codeSnippet,sizeof(char)*(tempi+2));
                        codeSnippet = slice(code,startPos,startPos+tempi);
                        result = regexTest(token.value,codeSnippet);
                        if(result == -1){
                            for(int tokenIndex = j-1; tokenIndex >= 0; tokenIndex--){
                                result = regexTest(lexerTokens[tokenIndex].value,codeSnippet);
                                if(result == 1){
                                    i = tempi;
                                    looping = false;
                                }
                            }
                            if(looping){
                                i = tempi-1;
                                codeSnippet = slice(codeSnippet,0,-2);
                            }
                            break;
                        }
                    }
                    if(token.type != WHITESPACE){
                        token.value = codeSnippet;
                        token.line = line;
                        tokenList = AddToTokenList(tokenList,token);
                    }
                    startPos+=i+1;
                    exitLoop = true;
                    break;
                }
            }
        }
    }
    return tokenList;
}