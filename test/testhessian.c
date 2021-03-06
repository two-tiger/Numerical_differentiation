#include <stdio.h>
#include <stdlib.h>
#include "math.h"
#include "myvector.h"
#include "function.h"
#include "vectorfunction.h"
#include <omp.h>

double f1(Vector *x)
{
    return sin(x->entry[0]) * x->entry[1] + exp(x->entry[1]) * x->entry[0] +
           cos(x->entry[2]) * exp(x->entry[0]) * exp(x->entry[1]);
}

double f2(Vector *x)
{
    return pow(x->entry[0], 2) * exp(x->entry[1]) * pow(x->entry[2], 4);
}

double f3(Vector *x)
{
    return cos(x->entry[0]) * pow(x->entry[1], 2) + exp(x->entry[1]) * x->entry[0] + x->entry[1] * x->entry[2];
}

double f4(Vector *x)
{
    return pow(x->entry[0], 2) + pow(x->entry[1], 2) + pow(x->entry[2], 2);
}

int main(void)
{
    
    NdsclaFunction *function1 = NdsclaFunctionAlloc(f1, 3, NULL, NULL);
    NdsclaFunction *function2 = NdsclaFunctionAlloc(f2, 3, NULL, NULL);
    NdsclaFunction *function3 = NdsclaFunctionAlloc(f3, 3, NULL, NULL);
    NdsclaFunction *function4 = NdsclaFunctionAlloc(f4, 3, NULL, NULL);
    Vector *x0 = VectorAlloc(3);
    x0->entry[0] = 1.0;
    x0->entry[1] = 2.0;
    x0->entry[2] = 3.8;
    Vector *hessian = VectorAlloc(function1->inputSize * function1->inputSize);
    double start, end;
    start = omp_get_wtime();
    HessianMatrixOMP(function1, x0, 0.01, hessian);
    end = omp_get_wtime();
    HessianPrint(hessian, function1->inputSize, function1->inputSize);
    printf("\n");
    printf("the time of HessianMatrix with omp is %d\n", end-start);
    start = omp_get_wtime();
    HessianMatrix(function1, x0, 0.01, hessian);
    end = omp_get_wtime();
    HessianPrint(hessian, function1->inputSize, function1->inputSize);
    printf("\n");
    printf("the time of HessianMatrix is %d\n", end-start);
}