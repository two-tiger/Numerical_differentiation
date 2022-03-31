#include "myvector.h"
#include <stdlib.h>
#include "function.h"
#include <omp.h>

NdsclaFunction *NdsclaFunctionAlloc(double (*function)(Vector *), int inputsize)
{
    NdsclaFunction *f = (NdsclaFunction *)malloc(sizeof(NdsclaFunction));
    f->function = function;
    f->inputSize = inputsize;
}

double NdsclaFunctionCall(NdsclaFunction *function, Vector *x)
{
    return function->function(x);
}

void *NdsclaFunctionFree(NdsclaFunction *function)
{
    free(function->function);
    free(function);
}

void centralGrad(NdsclaFunction *function, const double h, const Vector *x0, Vector *grad)
{

    Vector *temp = VectorAlloc(x0->size);
    VectorCopy(x0, temp);
    double f_add_h, f_sub_h;
#pragma omp for
{
    for (int i = 0; i < function->inputSize; i++)
    {
        temp->entry[i] += h;
        f_add_h = NdsclaFunctionCall(function, temp);
        temp->entry[i] -= 2 * h;
        f_sub_h = NdsclaFunctionCall(function, temp);
        temp->entry[i] += h;
        grad->entry[i] = (f_add_h - f_sub_h) / (2. * h);
    }
}
    VectorFree(temp);
}

void HessianMatrix(NdsclaFunction *function, const Vector *x0, double h, Vector *hessian)
{
    double f_ah1_ah2, f_ah1_sh2, f_sh1_ah2, f_sh1_sh2;
    for (int i = 0; i < function->inputSize; i++)
    {
        for (int j = 0; j < function->inputSize; j++)
        {
            Vector *temp = VectorAlloc(function->inputSize);
            VectorCopy(x0, temp);
            temp->entry[i] += h;
            temp->entry[j] += h;
            f_ah1_ah2 = NdsclaFunctionCall(function, temp);
            temp->entry[j] -= 2 * h;
            f_ah1_sh2 = NdsclaFunctionCall(function, temp);
            temp->entry[i] -= 2 * h;
            f_sh1_sh2 = NdsclaFunctionCall(function, temp);
            temp->entry[j] += 2 * h;
            f_sh1_ah2 = NdsclaFunctionCall(function, temp);
            hessian->entry[function->inputSize * i + j] = (f_ah1_ah2 - f_ah1_sh2 - f_sh1_ah2 + f_sh1_sh2) / (4*h*h);
        }
    }
}