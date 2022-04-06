#include <stdio.h>
#include <stdlib.h>
#include "math.h"
#include "function.h"
#include "myvector.h"
#include "mydual.h"
#include "mycomplex.h"

// sin(x1)*x2+e^x2*x1+cos(x3)*e^x1*e^x2
double f1(Vector *x)
{
    return sin(x->entry[0]) * x->entry[1] + exp(x->entry[1]) * x->entry[0] +
           cos(x->entry[2]) * exp(x->entry[0]) * exp(x->entry[1]);
}

Complex f1complex(Vector *x)
{
    Complex a, b, c;
    a = ComplexMul(ComplexSin(x->complexEntry[0]), x->complexEntry[1]);
    b = ComplexMul(ComplexExp(x->complexEntry[1]), x->complexEntry[0]);
    c = ComplexMul(ComplexMul(ComplexExp(x->complexEntry[0]), ComplexExp(x->complexEntry[1])), ComplexCos(x->complexEntry[2]));
    return ComplexAdd(ComplexAdd(a, b), c);
}

Dual f1dual(Vector *x)
{
    Dual a, b, c;
    a = DualMul(DualSin(x->dualEntry[0]), x->dualEntry[1]);
    b = DualMul(DualExp(x->dualEntry[1]), x->dualEntry[0]);
    c = DualMul(DualMul(DualExp(x->dualEntry[0]), DualExp(x->dualEntry[1])), DualCos(x->dualEntry[2]));
    return DualAdd(DualAdd(a, b), c);
}

double f2(Vector *x)
{
    return pow(x->entry[0], 2) +
           pow(x->entry[1], 2) +
           pow(x->entry[2], 2);
}

Dual f2dual(Vector *x)
{
    Dual a, b, c;
    a = DualMul(x->dualEntry[0], x->dualEntry[0]);
    b = DualMul(x->dualEntry[1], x->dualEntry[1]);
    c = DualMul(x->dualEntry[2], x->dualEntry[2]);
    return DualAdd(DualAdd(a, b), c);
}

int main(void)
{
    NdsclaFunction *fun = NdsclaFunctionAlloc(f2, 3, NULL, f2dual);
    Vector *x0 = VectorAlloc(3);
    x0->entry[0] = 1.0;
    x0->entry[1] = 2.0;
    x0->entry[2] = 3.8;
    Vector *centralgrad = VectorAlloc(3);
    Vector *dualgrad = VectorAlloc(3);
    centralGrad(fun, 0.01, x0, centralgrad);
    printf("the grad of function using central: ");
    VectorPrint(centralgrad);
    printf("\n");
    dualGrad(fun, x0, 0.01, dualgrad);
    printf("the grad of function using dual: ");
    VectorPrint(dualgrad);
    printf("\n");
    NdsclaFunction *fun2 = NdsclaFunctionAlloc(f1, 3, f1complex, f1dual);
    Vector *centralgrad2 = VectorAlloc(3);
    Vector *complexgrad2 = VectorAlloc(3);
    Vector *dualgrad2 = VectorAlloc(3);
    centralGrad(fun2, 0.01, x0, centralgrad2);
    printf("the grad of function using central: ");
    VectorPrint(centralgrad2);
    printf("\n");
    bicomplexGrad(fun2, x0, 0.01, complexgrad2);
    printf("the grad of function using complex: ");
    VectorPrint(complexgrad2);
    printf("\n");
    dualGrad(fun2, x0, 0.01, dualgrad2);
    printf("the grad of function using dual: ");
    VectorPrint(dualgrad2);
    printf("\n");
}