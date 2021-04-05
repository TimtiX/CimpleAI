#ifndef CAI_TOOLS_H
#define CAI_TOOLS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "string_tools.h"
#include "../core/cai_core.h"

void caiLoadFile(CAINetwork* network, char* path);
void caiSaveFile(CAINetwork* network, char* path);
void caiRandomize(CAINetwork* network, float low, float high);
void caiMix(CAINetwork* netA, float probA, CAINetwork* netB, float probB, CAINetwork* target);

#endif
