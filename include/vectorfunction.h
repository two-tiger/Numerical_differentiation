#pragma once
#include "myvector.h"
#include "function.h"

struct VectorFunction
{
    unsigned int inputSize;
    unsigned int outputSize;
    NdsclaFunction *Function;
};
typedef struct VectorFunction VectorFunction;

VectorFunction *VectorFunctionAlloc(int outputsize);
void *VectorFunctionFree(VectorFunction *F);
void JacobiMatrix(VectorFunction *Function, const Vector *x0, Matrix *jacobi);
