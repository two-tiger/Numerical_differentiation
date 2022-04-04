#include <stdio.h>
#include "mycomplex.h"
#include <complex.h>

int main(void)
{
    Complex x, y, p, q, r, s, e, l, n, c, t;
    x.re = 4.2;
    x.im = 1.5;
    y.re = 2.5;
    y.im = -0.3;
    p = ComplexAdd(x, y);
    ComplexPrint(p);
    printf("\n");
    q = ComplexSub(x, y);
    ComplexPrint(q);
    printf("\n");
    r = ComplexMul(x, y);
    ComplexPrint(r);
    printf("\n");
    s = ComplexDiv(x, y);
    ComplexPrint(s);
    printf("\n");
    e = ComplexExp(x);
    ComplexPrint(e);
    printf("\n");
    l = ComplexLog(x);
    ComplexPrint(l);
    printf("\n");
    n = ComplexSin(x);
    ComplexPrint(n);
    printf("\n");
    c = ComplexCos(x);
    ComplexPrint(c);
    printf("\n");
    t = ComplexTan(x);
    ComplexPrint(t);
    printf("\n");
    return 0;
}