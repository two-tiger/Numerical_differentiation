#pragma once

struct complex
{
    double re;
    double im;
};
typedef struct complex Complex;

Complex ComplexAdd(const Complex *x, const Complex *y);
Complex ComplexSub(const Complex *x, const Complex *y);
Complex ComplexMul(const Complex *x, const Complex *y);
Complex ComplexDiv(const Complex *x, const Complex *y);
void ComplexPrint(const Complex *complex);
