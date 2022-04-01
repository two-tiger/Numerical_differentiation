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
void centralGradOMP(NdsclaFunction *function, const double h, const Vector *x0, Vector *grad);
void centralGrad(NdsclaFunction *function, const double h, const Vector *x0, Vector *grad);
void HessianMatrixOMP(NdsclaFunction *function, const Vector *x0, double h, Vector *hessian);
void HessianMatrix(NdsclaFunction *function, const Vector *x0, double h, Vector *hessian);
