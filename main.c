#include <stdio.h>
#include <stdlib.h>
#include "core/cai_core.h"

int main() {
    CAINetwork* network = malloc(sizeof(CAINetwork));
    int sizes[] = {1, 2, 1}; //Network with 3 layers and the given neuron amounts
    caiInitializeNetwork(network, 3, sizes);

    float data0[] = {0.5, 0.5}; //Weights from layer 0 -> 1
    caiPutLayerData(network, 1, data0);

    float data1[] = {2.0, 2.0}; //Weights from layer 1 -> 2
    caiPutLayerData(network, 2, data1);

    float processData[] = {5.0}; //Data to prcoess as input
    caiProcessInput(network, processData);

    printf("%f\n", processData[0]); //Output should be 10.0

    caiDisposeNetwok(network);
    return 0;
}
