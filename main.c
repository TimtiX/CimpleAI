#include <stdio.h>
#include <time.h>
#include "core/cai_core.h"
#include "tools/cai_tools.h"

int main() {
    srand(time(NULL)); //Seed the random number generator

    CAINetwork network; //The network to develop
    int layerSizes[] = {2, 8, 8, 1};
    float score = 100000.0;

    caiInitializeNetwork(&network, 4, layerSizes); //Initialize and randomize the network
    caiRandomize(&network, -1.0, 1.0);

    for(int count = 0; count < 1000000; count++) {
        CAINetwork newNetwork; //Create a new random network

        caiInitializeNetwork(&newNetwork, 4, layerSizes);
        caiRandomize(&newNetwork, -1.0, 1.0);

        float processData[] = {5.0, 6.0}; //Process its result
        caiProcessInput(&newNetwork, processData);
        float newScore = abs(11.0 - processData[0]);

        if(newScore < score) { //Either use the new or old network based on their score
            caiDisposeNetwork(&network);
            network = newNetwork;
            score = newScore;
        } else
            caiDisposeNetwork(&newNetwork);
    }

    float processData[] = {5.0, 6.0}; //Print the result of the best network (~11.0)
    caiProcessInput(&network, processData);
    printf("6 + 5 = %f\n", processData[0]);

    caiDisposeNetwork(&network);
    return 0;
}
