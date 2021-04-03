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
