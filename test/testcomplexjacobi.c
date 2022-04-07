#include <stdio.h>
#include <stdlib.h>
#include "math.h"
#include "function.h"
#include "myvector.h"
#include <omp.h>
#include "mycomplex.h"
#include "vectorfunction.h"

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
    NdsclaFunction *function1 = NdsclaFunctionAlloc(f1, 3, f1complex, NULL);
    NdsclaFunction *function2 = NdsclaFunctionAlloc(f2, 3, f2complex, NULL);
    VectorFunction *testfunction = VectorFunctionAlloc(3, 2);
    testfunction->Function[0] = *function1;
    testfunction->Function[1] = *function2;
    Vector *x0 = VectorAlloc(3);
    x0->entry[0] = 1.0;
    x0->entry[1] = 2.0;
    x0->entry[2] = 3.8;
    Matrix *centraljacobi = MatrixAlloc(2, 3);
    Matrix *complexjacobi = MatrixAlloc(2, 3);
    JacobiMatrix(testfunction, x0, centraljacobi);
    printf("the jacobi matrix of function using central: ");
    printf("\n");
    MatrixPrint(centraljacobi);
    printf("\n");
    BicomplexJacobiMatrix(testfunction, x0, complexjacobi);
    printf("the jacobi matrix of function using complex: ");
    printf("\n");
    MatrixPrint(complexjacobi);
    printf("\n");
}