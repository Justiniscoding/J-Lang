#include "string.h"
char* slice(char* string,int start,int end){
    if(end < 0){
        end = strlen(string)+end;
    }
    char* buffer;
    buffer = (char*) malloc((end-start) * sizeof(char));
    size_t j = 0;
    for (size_t i = start; i <= end; ++i) {
        buffer[j++] = string[i];
    }
    buffer[j] = 0;
    return buffer;
}