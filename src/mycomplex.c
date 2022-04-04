#include <stdio.h>
#include <stdlib.h>
#include "mycomplex.h"
#include <math.h>
// #include <complex.h>

// 复数的模
double ComplexAbs(const Complex x)
{
    double m;
    m = sqrt(x.re * x.re + x.im * x.im);
    return m;
}

// 复数辐角
double ComplexArg(const Complex x)
{
    return atan2(x.im, x.re);
}

// 复数加法
Complex ComplexAdd(const Complex x, const Complex y)
{
    Complex p;
    p.re = x.re + y.re;
    p.im = x.im + y.im;
    return p;
}

// 复数减法
Complex ComplexSub(const Complex x, const Complex y)
{
    Complex q;
    q.re = x.re - y.re;
    q.im = x.im - y.im;
    return q;
}

// 复数乘法
Complex ComplexMul(const Complex x, const Complex y)
{
    Complex r;
    r.re = (x.re * y.re) - (x.im * y.im);
    r.im = (x.re * y.im) + (x.im * y.re);
    return r;
}

// 复数除法
Complex ComplexDiv(const Complex x, const Complex y)
{
    Complex div, s;
    if (y.re == 0 && y.im == 0)
    {
        printf("Divided by zero!\n");
        div.re = 0;
        div.im = 0;
        return div;
    }
    else
    {
        double w = y.re * y.re + y.im * y.im;
        s.re = (x.re * y.re + x.im * y.im)/w;
        s.im = (x.im * y.re - x.re * y.im)/w;
    }
    return s;
}

// 复数exp
Complex ComplexExp(const Complex x)
{
    Complex e;
    e.re = exp(x.re) * cos(x.im);
    e.im = exp(x.re) * sin(x.im);
    return e;
}

// 复数log(ln)
Complex ComplexLog(const Complex x)
{
    Complex l;
    l.re = log(x.re * x.re + x.im * x.im) / 2;
    l.im = 1 / tan(x.im / x.re);
    return l;
}

// 复数开n次方
Complex ComplexNRoot(const Complex x, int n)
{
    double abs = ComplexAbs(x);
    double abs_n = pow(abs, 1/n);
    double theta = ComplexArg(x);
    Complex arg;
    arg.re = 0;
    arg.im = theta / n;
    Complex root;
    root = ComplexExp(arg);
    root.re *= abs_n;
    root.im *= abs_n;
    return root;
}

// 复数sin
Complex ComplexSin(const Complex x)
{
    Complex s;
    s.re = sin(x.re) * cosh(x.im);
    s.im = cos(x.re) * sinh(x.im);
    return s;
}

// 复数cos
Complex ComplexCos(const Complex x)
{
    Complex c;
    c.re = cos(x.re) * cosh(x.im);
    c.im = - sin(x.re) * sinh(x.im);
    return c;
}

// 复数tan
Complex ComplexTan(const Complex x)
{
    Complex s, c, t;
    s = ComplexSin(x);
    c = ComplexCos(x);
    t = ComplexDiv(s, c);
    return t;
}

// 复数arcsin
// Complex ComplexArcsin(const Complex *x)
// {
//     Complex tmp, i, unit;
//     i.re = 0; i.im = 1;
//     unit.re = 1; unit.im = 0;
//     tmp = ComplexAdd(ComplexMul(&i, x),ComplexNRoot(ComplexSub(&unit,ComplexMul(x, x)),2));
//     tmp = ComplexLog(&tmp);
//     double sto;
//     sto = tmp.re;
//     tmp.re = tmp.im;
//     tmp.im = - sto;
//     return tmp;
// }

// 复数arccos

// 复数arctan

// 复数双曲函数

// 复数打印
void ComplexPrint(const Complex complex)
{
    printf("%g+%gi",complex.re, complex.im);
}