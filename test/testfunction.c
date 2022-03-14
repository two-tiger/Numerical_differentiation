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
    printf("%f", NdsclaFunctionCall(f, x0));
}