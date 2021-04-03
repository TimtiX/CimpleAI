#include "cai_tools.h"
#include "string_tools.h"

void caiLoadFile(CAINetwork* network, char* path) {
    FILE* file = fopen(path, "r");

    if(!file)
        return;

    fseek(file, 0L, SEEK_END);
    int fileSize = ftell(file);
    char* fileContent = (char*) malloc(sizeof(char) * (fileSize + 1));
    rewind(file);

    for(int index = 0; index < fileSize; index++)
        fileContent[index] = fgetc(file);

    fclose(file);
    fileContent[fileSize] = '\0';

    int lineAmount = splitString(fileContent, '\n');

    int fileContentIndex = 0;
    for(int lineIndex = 0; lineIndex < lineAmount; lineIndex++) {
        char* lineContent = copyString(fileContent + fileContentIndex);

        if(strlen(lineContent) == 0) {
            fileContentIndex += 1;
            free(lineContent);
            continue;
        }

        int partAmount = splitString(lineContent, ' ');

        if(lineIndex == 0) {
            int* layerSizes = (int*) malloc(sizeof(int) * partAmount);

            int lineContentIndex = 0;
            for(int partIndex = 0; partIndex < partAmount; partIndex++) {
                layerSizes[partIndex] = atoi(lineContent + lineContentIndex);
                lineContentIndex += strlen(lineContent + lineContentIndex) + 1;
            }

            caiInitializeNetwork(network, partAmount, layerSizes);

            free(layerSizes);
        } else {
            float* data = (float*) malloc(sizeof(float) * partAmount);

            int lineContentIndex = 0;
            for(int partIndex = 0; partIndex < partAmount; partIndex++) {
                data[partIndex] = atof(lineContent + lineContentIndex);
                lineContentIndex += strlen(lineContent + lineContentIndex) + 1;
            }

            caiPutLayerData(network, lineIndex, data);

            free(data);
        }

        free(lineContent);
        fileContentIndex += strlen(fileContent + fileContentIndex) + 1;
    }

    free(fileContent);
}

void caiSaveFile(CAINetwork* network, char* path) {

}

void caiRandomize(CAINetwork* network, float low, float high) {

}

void caiMix(CAINetwork* netA, float probA, CAINetwork* netB, float probB, CAINetwork* target) {

}
