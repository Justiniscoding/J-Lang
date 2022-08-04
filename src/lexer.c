#include "lexer.h"
const int tokenAmount = TOKEN_AMOUNT;

// Tokens & regex for lexer

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
        ARITHMETIC,
        "[+-x/]"
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
				// Get the token in the list from index j, and check if the current snippet of source code selected by the two loops matches the equivalent regex for the token

                Token token = lexerTokens[j];
                char* codeSnippet = malloc((startPos+i) * sizeof(char));
                strcpy(codeSnippet,slice(code,startPos,startPos+i));
                if(strcmp(codeSnippet,"") == 0){
                    break;
                }
                int result = regexTest(token.value,codeSnippet);

				// Run if the regex does match the token

                if(result == 1){

                    if(token.type == NEWLINE){
                        line++;
                    }

					// If the token is an identifier, check if including the next letter in the snippet keeps it an identifier. For example, if
					// the source code fed into the lexer is "abc123" and it recognizes that "a" is an identifier, it will keep trying to go
					// through the code and get "abc" as the new identifier and stop at "1" because an identifier consitst of letters a-z.
					//
					// TLDR: Expand the identifier string as long as possible

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

					// If the token is a dash/subtraction symbol("-"), check if the next character is a greater then arrow,
					// meaning that the token should instead be classified as an arrow token.

					if(token.type == ARITHMETIC){
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
							i++;
						}else{
							codeSnippet = realloc(codeSnippet,sizeof(char)*(i));
							strcpy(codeSnippet,slice(code,startPos,startPos+i));
						}
					}


					// Add the token to the list of tokens for the parser if it is not a whitespace token, because whitespace tokens are
					// (currently) unnessacary for the parser.

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