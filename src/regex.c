#include "regex.h"
int regexTest(char* regexString,char* testString){
    regex_t regex;
    int reti;
    char withEnd[strlen(regexString)+1];
    strcpy(withEnd,regexString);
    strcat(withEnd,"$");
    char final[strlen(regexString)+2];
    strcpy(final,"^");
    strcat(final,withEnd);
    reti = regcomp(&regex, final, 0);
    if (reti) {
        printf("Regex compilation failed");
        exit(1);
    }
    reti = regexec(&regex,testString,0,NULL,0);
    if(!reti){
        return 1;
    }else if(reti == REG_NOMATCH){
        return -1;
    }else{
        printf("Regex Matching Failed");
        exit(1);
    }
}