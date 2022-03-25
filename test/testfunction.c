#include <stdio.h>
#include <stdlib.h>
#include "math.h"
#include "function.h"
#include "myvector.h"

double target_function(Vector *mat)
{
    return pow(mat->entry[0], 2) +
           pow(mat->entry[1], 2) +
           pow(mat->entry[2], 2);
}

// sin(x1)*x2+e^x2*x1+cos(x3)*e^x1*e^x2
double f1(Vector *x)
{
    return sin(x->entry[0]) * x->entry[1] + exp(x->entry[1]) * x->entry[0] +
           cos(x->entry[2]) * exp(x->entry[0]) * exp(x->entry[1]);
}

int main(void)
{
    NdsclaFunction *f = NdsclaFunctionAlloc(target_function, 3);
    Vector *x0 = VectorAlloc(3);
    x0->entry[0] = 1.0;
    x0->entry[1] = 2.0;
    x0->entry[2] = 2.0;
    Vector *grad = VectorAlloc(3);
    centralGrad(f, 0.01, x0, grad);
    VectorPrint(grad);
    printf("\n");
    NdsclaFunction *fun = NdsclaFunctionAlloc(f1, 3);
    Vector *x0_fun = VectorAlloc(3);
    x0_fun->entry[0] = 1.0;
    x0_fun->entry[1] = 2.0;
    x0_fun->entry[2] = 3.8;
    Vector *grad_fun = VectorAlloc(3);
    centralGrad(fun, 0.01, x0_fun, grad_fun);
    VectorPrint(grad_fun);
}