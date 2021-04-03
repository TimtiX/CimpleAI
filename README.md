**CimpleAI**

This is a small project to learn a bit about C and AI. The idea is to have a command line tool that can evolve neural networks. A more detailed documentation will follow. The project is in early development and as I am currently graduating there will not be much activity until mid 2021.

---

**Setup/Compiling**

On linux:
```bash
sudo apt-get install gcc
gcc main.c core/cai_core.c -o out.o
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
