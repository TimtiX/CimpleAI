#include "file_tools.h"

char* loadFileString(char* path, int* size) {
    FILE* file = fopen(path, "r");

    if(!file) {
        *size = -1;
        return 0;
    }

    fseek(file, 0L, SEEK_END);
    int fileSize = ftell(file);
    char* fileContent = (char*) malloc(sizeof(char) * (fileSize + 1));
    rewind(file);

    for(int index = 0; index < fileSize; index++)
        fileContent[index] = fgetc(file);

    fclose(file);
    fileContent[fileSize] = '\0';

    *size = fileSize;
    return fileContent;
}
