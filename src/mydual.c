#include <stdio.h>
#include <stdlib.h>
#include "mydual.h"
#include <math.h>

// 对偶数的模
double DualAbs(const Dual x)
{
    return fabs(x.re);
}

// 对偶数共轭
Dual DualCon(const Dual x)
{
    Dual c;
    c.re = x.re;
    c.du = - x.du;
    return c;
}

// 对偶数的逆
Dual DualInv(const Dual x)
{
    Dual p, s;
    double tmp;
    s = DualCon(x);
    tmp = pow(DualAbs(x), 2);
    p.re = s.re / tmp;
    p.du = s.du / tmp;
    return p;
}

// 对偶数加法
Dual DualAdd(const Dual x, const Dual y)
{
    Dual a;
    a.re = x.re + y.re;
    a.du = x.du + y.du;
    return a;
}

// 对偶数减法
Dual DualSub(const Dual x, const Dual y)
{
    Dual b;
    b.re = x.re - y.re;
    b.du = x.du - y.du;
    return b;
}

// 对偶数乘法
Dual DualMul(const Dual x, const Dual y)
{
    Dual m;
    m.re = x.re * y.re;
    m.du = x.re * y.du + x.du * y.re;
    return m;
}

// 对偶数除法
Dual DualDiv(const Dual x, const Dual y)
{
    Dual div, s;
    if (y.re == 0)
    {
        printf("Divided by zero!\n");
        div.re = 0;
        div.du = y.du;
        return div;
    }
    else
    {
        s.re = x.re / y.re;
        s.du = (x.du * y.re - x.re * y.du) / (y.re * y.re);
    }
    return s;
}

// 对偶数exp
Dual DualExp(const Dual x)
{
    Dual e;
    e.re = exp(x.re);
    e.du = exp(x.re) * x.du;
    return e;
}

// 对偶数log(ln)
Dual DualLog(const Dual x)
{
    Dual l;
    l.re = log(x.re);
    l.du = x.du / x.re;
    return l;
}

// 对偶数sin
Dual DualSin(const Dual x)
{
    Dual s;
    s.re = sin(x.re);
    s.du = cos(x.re) * x.du;
    return s;
}

// 对偶数cos
Dual DualCos(const Dual x)
{
    Dual c;
    c.re = cos(x.re);
    c.du = - sin(x.re) * x.du;
    return c;
}

// 对偶数tan
Dual DualTan(const Dual x)
{
    Dual s, c, t;
    s = DualSin(x);
    c = DualCos(x);
    t = DualDiv(s, c);
    return t;
}

// 对偶数打印
void DualPrint(const Dual dual)
{
    printf("%g+%ge", dual.re, dual.du);
}