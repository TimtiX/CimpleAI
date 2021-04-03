#include "string_tools.h"

int splitString(char* string, char split) {
    int arrayLength = 1;
    int stringLength = strlen(string);
    for(int index = 0; index < stringLength; index++) {
        char c = string[index];

        if(c == split) {
            string[index] = '\0';
            arrayLength++;
        }
    }

    return arrayLength;
}

char* copyString(char* string) {
    int stringLength = strlen(string);
    char* copy = (char*) malloc(sizeof(char) * (stringLength + 1));
    copy[stringLength] = '\0';
    strcpy(copy, string);
}
