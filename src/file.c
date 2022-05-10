#include "file.h"
char* fileRead(char* path) {
	FILE* file = fopen(path, "r");
	if (!file) {
		printf("Could not open file \"%s\"\n", path);
		return NULL;
	}
	fseek(file, 0, SEEK_END);
	int filesize = ftell(file);
	fseek(file, 0, SEEK_SET);
	char* buffer = (char*) malloc(sizeof(char)*(filesize+1));
	if (!buffer) {
		return NULL;
	}
	fread(buffer, 1, filesize, file);
	buffer[filesize] = '\0';
	fclose(file);
	return buffer;
}