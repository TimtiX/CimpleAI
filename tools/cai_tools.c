#include "cai_tools.h"

void caiLoadFile(CAINetwork* network, char* path) {
    int fileSize;
    char* fileContent = loadFileString(path, &fileSize);

    if(fileSize == -1)
        return;

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
    FILE* file = fopen(path, "w");

    if(!file)
        return;

    fprintf(file, "%i", network->layers[0]->weightAmount);

    for(int index = 0; index < network->layerAmount - 1; index++)
        fprintf(file, " %i", network->layers[index]->neuronAmount);

    fprintf(file, "\n");

    for(int layerIndex = 1; layerIndex < network->layerAmount; layerIndex++) {
        int dataSize = caiGetLayerDataSize(network, layerIndex);
        float* data = (float*) malloc(sizeof(float) * dataSize);

        caiGetLayerData(network, layerIndex, data);

        fprintf(file, "%f", data[0]);

        for(int dataIndex = 1; dataIndex < dataSize; dataIndex++)
            fprintf(file, " %f", data[dataIndex]);

        fprintf(file, "\n");
        free(data);
    }

    fclose(file);
}

void caiRandomize(CAINetwork* network, float low, float high) {
    for(int layerIndex = 1; layerIndex < network->layerAmount; layerIndex++) {
        int dataSize = caiGetLayerDataSize(network, layerIndex);
        float* data = (float*) malloc(sizeof(float) * dataSize);

        for(int dataIndex = 0; dataIndex < dataSize; dataIndex++)
            data[dataIndex] = ((float) rand() / (float) RAND_MAX) * (high - low) + low;

        caiPutLayerData(network, layerIndex, data);
        free(data);
    }
}

void caiMix(CAINetwork* netA, float probA, CAINetwork* netB, float probB, CAINetwork* target) {

}

float* caiLoadDataFile(char* path, int* setAmount) {
    return 0;
}
