#include <stdio.h>
#include <stdlib.h>
#include "math.h"
#include "myvector.h"
#include "function.h"
#include "vectorfunction.h"

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
    NdsclaFunction *function1 = NdsclaFunctionAlloc(f1, 3);
    NdsclaFunction *function2 = NdsclaFunctionAlloc(f2, 3);
    NdsclaFunction *function3 = NdsclaFunctionAlloc(f3, 3);
    NdsclaFunction *function4 = NdsclaFunctionAlloc(f4, 3);
    VectorFunction *testFunction = VectorFunctionAlloc(3, 4);
    testFunction->Function[0] = *function1;
    testFunction->Function[1] = *function2;
    testFunction->Function[2] = *function3;
    testFunction->Function[3] = *function4;
    Vector *x0 = VectorAlloc(3);
    x0->entry[0] = 1.0;
    x0->entry[1] = 2.0;
    x0->entry[2] = 3.8;
    Matrix *jacobi = MatrixAlloc(4,3);
    JacobiMatrix(testFunction, x0, jacobi);
    MatrixPrint(jacobi);
}