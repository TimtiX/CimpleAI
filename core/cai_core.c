#include <stdio.h>
#include "cai_core.h"

void caiInitializeNetwork(CAINetwork* network, int layerAmount, int* layerSizes) {
    if(layerAmount < 1)
        return;

    for(int index = 0; index < layerAmount; index++)
        if(layerSizes[index] < 1)
            return;

    network->activationFunc = CAI_LINEAR;
    network->layerAmount = layerAmount;
    network->layers = (CAILayer**) malloc(sizeof(CAILayer*) * (layerAmount - 1));

    for(int layerIndex = 1; layerIndex < layerAmount; layerIndex++) {
        CAILayer* layer = (CAILayer*) malloc(sizeof(CAILayer));
        layer->neuronAmount = layerSizes[layerIndex];
        layer->weightAmount = layerSizes[layerIndex - 1];
        layer->weightData = (float*) malloc(sizeof(float) * layer->neuronAmount * layer->weightAmount);
        network->layers[layerIndex - 1] = layer;
    }
}

void caiDisposeNetwok(CAINetwork* network) {
    for(int layerIndex = 1; layerIndex < network->layerAmount; layerIndex++) {
        CAILayer* layer = network->layers[layerIndex - 1];
        free(layer->weightData);
        free(layer);
    }

    free(network);
}

void caiGetLayerData(CAINetwork* network, int layerIndex, float* target) {
    if(layerIndex >= 1 && layerIndex < network->layerAmount) {
        CAILayer* layer = network->layers[layerIndex - 1];
        float* data = layer->weightData;
        int dataSize = layer->neuronAmount * layer->weightAmount;

        for(int index = 0; index < dataSize; index++)
            target[index] = data[index];
    }
}

void caiPutLayerData(CAINetwork* network, int layerIndex, float* data) {
    if(layerIndex >= 1 && layerIndex < network->layerAmount) {
        CAILayer* layer = network->layers[layerIndex - 1];
        float* target = layer->weightData;
        int dataSize = layer->neuronAmount * layer->weightAmount;

        for(int index = 0; index < dataSize; index++)
            target[index] = data[index];
    }
}

void caiProcessInput(CAINetwork* network, float* data) {
    float* currentData;
    float* currentBuffer;

    int inputSize = caiGetInputSize(network);
    currentData = (float*) malloc(sizeof(float) * inputSize);
    for(int index = 0; index < inputSize; index++)
        currentData[index] = data[index];

    for(int layerIndex = 1; layerIndex < network->layerAmount; layerIndex++) {
        CAILayer* layer = network->layers[layerIndex - 1];
        currentBuffer = (float*) malloc(sizeof(float) * layer->neuronAmount);

        for(int neuronIndex = 0; neuronIndex < layer->neuronAmount; neuronIndex++) {
            currentBuffer[neuronIndex] = 0.0;

            for(int weightIndex = 0; weightIndex < layer->weightAmount; weightIndex++) {
                int layerDataIndex = caiGetLayerDataIndex(network, layerIndex, neuronIndex, weightIndex);
                currentBuffer[neuronIndex] += currentData[weightIndex] * layer->weightData[layerDataIndex];
            }
        }

        free(currentData);
        currentData = currentBuffer;
    }

    int outputSize = caiGetOutputSize(network);
    for(int index = 0; index < outputSize; index++)
        data[index] = currentData[index];

    free(currentData);
}

void caiSetActivationFunc(CAINetwork* network, int activationFunc) {
    network->activationFunc = activationFunc;
}

int caiGetLayerAmount(CAINetwork* network) {
    return network->layerAmount;
}

int caiGetNeuronAmount(CAINetwork* network, int layerIndex) {
    if(layerIndex < 0 || layerIndex >= network->layerAmount)
        return -1;

    if(layerIndex == 0)
        return network->layers[0]->weightAmount;

    return network->layers[layerIndex - 1]->neuronAmount;
}

int caiGetWeightAmount(CAINetwork* network, int layerIndex) {
    if(layerIndex < 1 || layerIndex >= network->layerAmount)
        return -1;

    return network->layers[layerIndex - 1]->weightAmount;
}

int caiGetLayerDataSize(CAINetwork* network, int layerIndex) {
    if(layerIndex < 1 || layerIndex >= network->layerAmount)
        return -1;

    CAILayer* layer = network->layers[layerIndex - 1];
    return layer->neuronAmount * layer->weightAmount;
}

int caiGetActivationFunc(CAINetwork* network) {
    return network->activationFunc;
}

int caiGetLayerDataIndex(CAINetwork* network, int layerIndex, int neuronIndex, int weightIndex) {
    if(layerIndex < 1 || layerIndex >= network->layerAmount)
        return -1;

    CAILayer* layer = network->layers[layerIndex - 1];

    if(neuronIndex < 0 || neuronIndex >= layer->neuronAmount)
        return -1;

    if(weightIndex < 0 || weightIndex >= layer->weightAmount)
        return -1;

    return neuronIndex * layer->weightAmount + weightIndex;
}

int caiGetInputSize(CAINetwork* network) {
    return caiGetWeightAmount(network, 1);
}

int caiGetOutputSize(CAINetwork* network) {
    return caiGetNeuronAmount(network, network->layerAmount - 1);
}
