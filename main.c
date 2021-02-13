#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "neural_network.h"

float scoreNetwork(NeuralNetwork* network);
float absNum(float f);

int main() {
    int layers[] = {2, 4, 16, 4, 2};
    NeuralNetwork* currentNetwork = createNeuralNetwork(5, layers);
    float currentScore = 10000.0;

    for(int i = 0; i < 2500000; i++) {
        NeuralNetwork* newNetwork = createNeuralNetwork(5, layers);
        float newScore = scoreNetwork(newNetwork);

        if(newScore < currentScore) {
            deleteNeuralNetwork(currentNetwork);
            currentNetwork = newNetwork;
            currentScore = newScore;
        } else
            deleteNeuralNetwork(newNetwork);
    }

    for(int i = 0; i < 8; i++) {
        float numA = (float) rand() / (float) RAND_MAX;
        float numB = (float) rand() / (float) RAND_MAX;
        float result[] = {numA, numB};
        processNetworkInput(result, currentNetwork);
        float difference = absNum((numA + numB) - result[0]);
        printf("%f + %f -> %f (%f)\n", numA, numB, result[0], difference);
    }

    deleteNeuralNetwork(currentNetwork);

    return 0;
}

float scoreNetwork(NeuralNetwork* network) {
    time_t t;
    srand((unsigned) time(&t));
    float totalDifference = 0;

    for(int i = 0; i < 128; i++) {
        float numA = (float) rand() / (float) RAND_MAX;
        float numB = (float) rand() / (float) RAND_MAX;
        float result[] = {numA, numB};
        processNetworkInput(result, network);
        totalDifference += absNum((numA + numB) - result[0]);
    }

    return totalDifference / 128.0;
}

float absNum(float f) {
    return f < 0 ? -f : f;
}
