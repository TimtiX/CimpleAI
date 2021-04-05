**CimpleAI**

This is a small project to learn a bit about C and AI. The idea is to have a command line tool that can evolve neural networks. A more detailed documentation will follow. The project is in early development and as I am currently graduating there will not be much activity until mid 2021.

---

**Setup/Compiling**

On linux:
```bash
sudo apt-get install gcc
gcc main.c core/cai_core.c tools/cai_tools.c tools/string_tools.c -o out.o
./out.o
```

---

**Examples**

Some examples for main.c:
```C
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

    float processData[] = {5.0}; //Data to process as input
    caiProcessInput(network, processData);

    printf("%f\n", processData[0]); //Output should be 10.0

    caiDisposeNetwok(network);
    return 0;
}
```

Same as above, but loaded from a text file:
```C
#include <stdio.h>
#include <stdlib.h>
#include "core/cai_core.h"
#include "tools/cai_tools.h"

int main() {
    CAINetwork* network = malloc(sizeof(CAINetwork));
    caiLoadFile(network, "test.txt"); //Load network data from file test.txt

    float processData[] = {5.0}; //Data to process as input
    caiProcessInput(network, processData);

    printf("%f\n", processData[0]); //Output should be 10.0

    caiDisposeNetwok(network);
    return 0;
}
```

Here is a more practical example. It tries to find a network, that can calculate 6 + 5 as precise as possible. Remember, the code is not optimized to make the steps as clear as possible:
```C
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "core/cai_core.h"
#include "tools/cai_tools.h"

int main() {
    time_t t; //Initialize the random number generator
    srand(time(NULL));

    CAINetwork* network = malloc(sizeof(CAINetwork)); //The network to develop
    int layerSizes[] = {2, 8, 8, 1};
    float score = 100000.0;

    caiInitializeNetwork(network, 4, layerSizes); //Initialize and randomize the network
    caiRandomize(network, -1.0, 1.0);

    for(int count = 0; count < 1000000; count++) {
        CAINetwork* newNetwork = malloc(sizeof(CAINetwork)); //Create a new random network

        caiInitializeNetwork(newNetwork, 4, layerSizes);
        caiRandomize(newNetwork, -1.0, 1.0);

        float processData[] = {5.0, 6.0}; //Process its result
        caiProcessInput(newNetwork, processData);
        float newScore = abs(11.0 - processData[0]);

        if(newScore < score) { //Either use the new or old network based on their score
            caiDisposeNetwok(network);
            network = newNetwork;
            score = newScore;
        } else
            caiDisposeNetwok(newNetwork);
    }

    float processData[] = {5.0, 6.0}; //Print the result of the best network (~11.0)
    caiProcessInput(network, processData);
    printf("6 + 5 = %f\n", processData[0]);

    caiDisposeNetwok(network);
    return 0;
}
```
