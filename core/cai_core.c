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
        CAILayer* layer = network->layers[layerIndex];
        float* data = layer->weightData;
        int dataSize = layer->neuronAmount * layer->weightAmount;

        for(int index = 0; index < dataSize; index++)
            target[index] = data[index];
    }
}

void caiPutLayerData(CAINetwork* network, int layerIndex, float* data) {
    if(layerIndex >= 1 && layerIndex < network->layerAmount) {
        CAILayer* layer = network->layers[layerIndex];
        float* target = layer->weightData;
        int dataSize = layer->neuronAmount * layer->weightAmount;

        for(int index = 0; index < dataSize; index++)
            target[index] = data[index];
    }
}

void caiProcessInput(CAINetwork* network, float* data) {
    printf("Unsupported operation: caiProcessInput\n");
}

void caiSetActivationFunc(CAINetwork* network, int activationFunc) {
    network->activationFunc = activationFunc;
}

int caiGetLayerAmount(CAINetwork* network) {
    return network->layerAmount;
}

int caiGetNeuronAmount(CAINetwork* network, int layerIndex) {
    if(layerIndex < 1 || layerIndex >= network->layerAmount)
        return -1;

    return network->layers[layerIndex]->neuronAmount;
}

int caiGetWeightAmount(CAINetwork* network, int layerIndex) {
    if(layerIndex < 1 || layerIndex >= network->layerAmount)
        return -1;

    return network->layers[layerIndex]->weightAmount;
}

int caiGetLayerDataSize(CAINetwork* network, int layerIndex) {
    if(layerIndex < 1 || layerIndex >= network->layerAmount)
        return -1;

    CAILayer* layer = network->layers[layerIndex];
    return layer->neuronAmount * layer->weightAmount;
}

int caiGetActivationFunc(CAINetwork* network) {
    return network->activationFunc;
}
