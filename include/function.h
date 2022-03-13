#include "myvector.h"
#pragma once
struct NdsclaFunction
{
    unsigned int inputSize;
    double (*function)(Vector *);
};
typedef struct NdsclaFunction NdsclaFunction;

NdsclaFunction *NdsclaFunctionAlloc(double (*function)(Vector *), int inputsize);
double NdsclaFunctionCall(NdsclaFunction *function, Vector *x);
void *NdsclaFunctionFree(NdsclaFunction *function);
void centralGrad(NdsclaFunction *function, const double h, const Vector *x0, Vector *grad);
