#include <stdlib.h>
#include "myvector.h"
#include "function.h"
#include "vectorfunction.h"

VectorFunction *VectorFunctionAlloc(int inputsize, int outputsize)
{
    VectorFunction *F = (VectorFunction *)malloc(sizeof(VectorFunction));
    F->Function = (NdsclaFunction *)malloc(sizeof(NdsclaFunction) * outputsize);
    F->inputSize = inputsize;
    F->outputSize = outputsize;
    return F;
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
        centralGrad(&(Function->Function[i]), 0.01, x0, (jacobi->grad[i]));
    }
}

void HessianMatrix(VectorFunction *Function, const Vector *x0, double h, Vector *hessian)
{
    double f_ah1_ah2, f_ah1_sh2, f_sh1_ah2, f_sh1_sh2;
    for (int i = 0; i < Function->outputSize; i++)
    {
        for (int j = 0; j < Function->inputSize; j++)
        {
            Vector *temp = VectorAlloc(Function->inputSize);
            VectorCopy(x0, temp);
            temp->entry[i] += h;
            temp->entry[j] += h;
            f_ah1_ah2 = NdsclaFunctionCall(Function->Function, temp);
            temp->entry[j] -= 2 * h;
            f_ah1_sh2 = NdsclaFunctionCall(Function->Function, temp);
            temp->entry[i] -= 2 * h;
            f_sh1_sh2 = NdsclaFunctionCall(Function->Function, temp);
            temp->entry[j] += 2 * h;
            f_sh1_ah2 = NdsclaFunctionCall(Function->Function, temp);
            hessian->entry[Function->outputSize * i + j] = (f_ah1_ah2 - f_ah1_sh2 - f_sh1_ah2 + f_sh1_sh2) / (4*h*h);
        }
    }
}