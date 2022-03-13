#include <stdlib.h>
#include "myvector.h"
#include "function.h"
#include "vectorfunction.h"

VectorFunction *VectorFunctionAlloc(int outputsize)
{
    VectorFunction *F = (VectorFunction *)malloc(sizeof(VectorFunction));
    F->Function = (NdsclaFunction *)malloc(sizeof(NdsclaFunction)*outputsize);
    F->outputSize = outputsize;
}

void *VectorFunctionFree(VectorFunction *F)
{
    free(F->Function);
    free(F);
}

void JacobiMatrix(VectorFunction *Function, const Vector *x0, Matrix *jacobi)
{
    for (size_t i = 0; i < jacobi->rowSize; i++)
    {
        centralGrad(&(Function->Function[i]), 0.01, x0, &(jacobi->grad[i]));
    }
}