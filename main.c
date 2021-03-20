#include <stdio.h>
#include <stdlib.h>
#include "core/cai_core.h"

int main() {
    CAINetwork* network = malloc(sizeof(CAINetwork));
    int sizes[] = {1, 2, 1};

    caiInitializeNetwork(network, 3, sizes);

    float data[] = {6.0, 9.0};
    caiPutLayerData(network, 1, data);
    caiGetLayerData(network, 1, data);

    printf("%f\n%f\n", data[0], data[1]);

    caiDisposeNetwok(network);

    return 0;
}
