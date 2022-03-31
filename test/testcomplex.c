#include <stdio.h>
#include "mycomplex.h"
#include <complex.h>

int main(void)
{
    Complex x, y, p, q, r, s;
    x.re = 4.2;
    x.im = 1.5;
    y.re = 2.5;
    y.im = -0.3;
    p = ComplexAdd(&x, &y);
    ComplexPrint(&p);
    printf("\n");
    q = ComplexSub(&x, &y);
    ComplexPrint(&q);
    printf("\n");
    r = ComplexMul(&x, &y);
    ComplexPrint(&r);
    printf("\n");
    s = ComplexDiv(&x, &y);
    ComplexPrint(&s);
    printf("\n");
    return 0;
}