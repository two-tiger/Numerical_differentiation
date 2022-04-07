#include <stdio.h>
#include <stdlib.h>
#include "math.h"
#include "function.h"
#include "myvector.h"
#include <omp.h>
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

double f2(Vector *x)
{
    return pow(x->entry[0], 2) +
           pow(x->entry[1], 2) +
           pow(x->entry[2], 2);
}

Complex f2complex(Vector *x)
{
    Complex a, b, c;
    a = ComplexMul(x->complexEntry[0],x->complexEntry[0]);
    b = ComplexMul(x->complexEntry[1],x->complexEntry[1]);
    c = ComplexMul(x->complexEntry[2],x->complexEntry[2]);
    return ComplexAdd(ComplexAdd(a, b), c);
}

int main(void)
{
    NdsclaFunction *fun = NdsclaFunctionAlloc(f1, 3, f1complex, NULL);
    Vector *x0 = VectorAlloc(3);
    x0->entry[0] = 1.0;
    x0->entry[1] = 2.0;
    x0->entry[2] = 3.8;
    Vector *centralgrad = VectorAlloc(3);
    Vector *complexgrad = VectorAlloc(3);
    centralGrad(fun, 0.01, x0, centralgrad);
    printf("the grad of function using central: ");
    VectorPrint(centralgrad);
    printf("\n");
    bicomplexGrad(fun, x0, 0.01, complexgrad);
    printf("the grad of function using complex: ");
    VectorPrint(complexgrad);
    printf("\n");
    NdsclaFunction *fun1 = NdsclaFunctionAlloc(f2, 3, f2complex, NULL);
    Vector *x1 = VectorAlloc(3);
    x1->entry[0] = 1.0;
    x1->entry[1] = 2.0;
    x1->entry[2] = 3.8;
    Vector *centralgrad1 = VectorAlloc(3);
    Vector *complexgrad1 = VectorAlloc(3);
    centralGrad(fun1, 0.01, x1, centralgrad1);
    printf("the grad of function using central: ");
    VectorPrint(centralgrad1);
    printf("\n");
    bicomplexGrad(fun1, x1, 0.01, complexgrad1);
    printf("the grad of function using complex: ");
    VectorPrint(complexgrad1);
    printf("\n");
}