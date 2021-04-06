#ifndef CAI_CORE_H
#define CAI_CORE_H

#include <stdio.h>
#include <stdlib.h>

#define CAI_LINEAR 0

typedef struct CAILayerStruct {
    int neuronAmount;
    int weightAmount;
    float* weightData;
} CAILayer;

typedef struct CAINetworkStruct {
    int layerAmount;
    CAILayer** layers;
    int activationFunc;
} CAINetwork;

void caiInitializeNetwork(CAINetwork* network, int layerAmount, int* layerSizes);
void caiDisposeNetwork(CAINetwork* network);
void caiGetLayerData(CAINetwork* network, int layerIndex, float* target);
void caiPutLayerData(CAINetwork* network, int layerIndex, float* data);
void caiProcessInput(CAINetwork* network, float* data);
void caiSetActivationFunc(CAINetwork* network, int activationFunc);
int caiGetLayerAmount(CAINetwork* network);
int caiGetNeuronAmount(CAINetwork* network, int layerIndex);
int caiGetWeightAmount(CAINetwork* network, int layerIndex);
int caiGetLayerDataSize(CAINetwork* network, int layerIndex);
int caiGetLayerDataIndex(CAINetwork* network, int layerIndex, int neuronIndex, int weightIndex);
int caiGetActivationFunc(CAINetwork* network);
int caiGetInputSize(CAINetwork* network);
int caiGetOutputSize(CAINetwork* network);

#endif
