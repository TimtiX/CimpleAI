#include <stdlib.h>
#include <time.h>
#include "neural_network.h"

NeuronLayer* createNeuronLayer(int neuronAmount, int weightAmount) {
    NeuronLayer* layer = (NeuronLayer*) malloc(sizeof(NeuronLayer));
    layer->neuronWeights = (float*) malloc(sizeof(float) * neuronAmount * weightAmount);
    layer->neuronAmount = neuronAmount;
    layer->weightAmount = weightAmount;

    time_t t;
    srand((unsigned) time(&t));

    for(int i = 0; i < neuronAmount * weightAmount; i++)
        *(layer->neuronWeights + i) = (float) rand() / (float) RAND_MAX;

    return layer;
}

int getNeuronWeightIndex(NeuronLayer* layer, int neuron, int weight) {
    return neuron * layer->weightAmount + weight;
}

void deleteNeuronLayer(NeuronLayer* layer) {
    free((void*) layer->neuronWeights);
    free((void*) layer);
}

NeuralNetwork* createNeuralNetwork(int layerAmount, int* layerSizes) {
    NeuralNetwork* network = (NeuralNetwork*) malloc(sizeof(NeuralNetwork));
    network->layers = (NeuronLayer**) malloc((layerAmount - 1) * sizeof(NeuronLayer*));
    network->layerAmount = layerAmount;

    for(int i = 0; i < (layerAmount - 1); i++) {
        NeuronLayer* layer = createNeuronLayer(*(layerSizes + i + 1), *(layerSizes + i));
        *(network->layers + i) = layer;
    }

    return network;
}

void processNetworkInput(float* input, NeuralNetwork* network) {
    int resultSize = (*(network->layers))->weightAmount;
    float* result = (float*) malloc(sizeof(float) * resultSize);

    for(int i = 0; i < resultSize; i++)
        result[i] = input[i];

    for(int i = 0; i < network->layerAmount - 1; i++) {
        NeuronLayer* layer = network->layers[i];
        int newResultSize = layer->neuronAmount;
        float* newResult = (float*) malloc(sizeof(float) * newResultSize);

        for(int j = 0; j < layer->neuronAmount; j++) {
            *(newResult + j) = 0.0;
            for(int k = 0; k < layer->weightAmount; k++)
                newResult[j] += result[k] * layer->neuronWeights[getNeuronWeightIndex(layer, j, k)];
        }

        free(result);
        result = newResult;
        resultSize = newResultSize;
    }

    for(int i = 0; i < resultSize; i++)
        input[i] = result[i];

    free(result);
}

void deleteNeuralNetwork(NeuralNetwork* network) {
    for(int i = 0; i < network->layerAmount - 1; i++)
        deleteNeuronLayer(*(network->layers + i));

    free((void*) network->layers);
    free((void*) network);
}


void printNN(NeuralNetwork* network) {
    for(int i = 0; i < network->layerAmount - 1; i++) {
        printNL(*(network->layers + i));
        printf("\n\n");
    }
}

void printNL(NeuronLayer* layer) {
    for(int neuronI = 0; neuronI < layer->neuronAmount; neuronI++) {
        for(int weightI = 0; weightI < layer->weightAmount; weightI++)
            printf("%f ", *(layer->neuronWeights + getNeuronWeightIndex(layer, neuronI, weightI)));
        printf("\n");
    }
}
