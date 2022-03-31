#include <stdio.h>
#include "mycomplex.h"

// 复数加法
Complex ComplexAdd(const Complex *x, const Complex *y)
{
    Complex p;
    p.re = x->re + y->re;
    p.im = x->im + y->im;
    return p;
}

// 复数减法
Complex ComplexSub(const Complex *x, const Complex *y)
{
    Complex q;
    q.re = x->re - y->re;
    q.im = x->im - y->im;
    return q;
}

// 复数乘法
Complex ComplexMul(const Complex *x, const Complex *y)
{
    Complex r;
    r.re = (x->re * y->re) - (x->im * y->im);
    r.im = (x->re * y->im) + (x->im * y->re);
    return r;
}

// 复数除法
Complex ComplexDiv(const Complex *x, const Complex *y)
{
    Complex s;
    if (y->re == 0 && y->im == 0)
    {
        printf("Divided by zero!\n");
        return *y;
    }
    else
    {
        double w = y->re * y->re + y->im * y->im;
        s.re = (x->re * y->re + x->im * y->im)/w;
        s.im = (x->im * y->re - x->re * y->im)/w;
    }
    return s;
}

// 复数打印
void ComplexPrint(const Complex *complex)
{
    printf("%g+%gi",complex->re,complex->im);
}