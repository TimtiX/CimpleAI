#ifndef NEURAL_NETWORK_H
#define NEURAL_NETWORK_H

#include <stdio.h>
#include <stdlib.h>

/*
* A layer is just a matrix, represented by the neuronWeights pointer in a
* row-major format. Each row contains the weights from the last layer to one
* neuron in this layer. So the amount of rows corresponds to the amount of
* neurons in this layer and the amount of columns to the amount of neurons in
* the last layer. WeightAmount indicates the last layers neuron count.
*/
typedef struct NeuronLayerStruct {
    float* neuronWeights;
    int neuronAmount;
    int weightAmount;
} NeuronLayer;

/*
* A network is just an array of layers. The input size is determend by the
* weightAmount of the first layer. The outsize is determend by the neuronAmount
* of the last layer.
*/
typedef struct NeuralNetworkStruct {
    NeuronLayer** layers;
    int layerAmount;
} NeuralNetwork;

NeuronLayer* createNeuronLayer(int neuronAmount, int weightAmount);
int getNeuronWeightIndex(NeuronLayer* layer, int neuron, int weight);
void deleteNeuronLayer(NeuronLayer* layer);
NeuralNetwork* createNeuralNetwork(int layerAmount, int* layerSizes);
void processNetworkInput(float* input, NeuralNetwork* network);
void printNN(NeuralNetwork* network);
void printNL(NeuronLayer* layer);
void deleteNeuralNetwork(NeuralNetwork* network);

#endif
