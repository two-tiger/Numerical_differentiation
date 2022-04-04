#pragma once

struct complex
{
    double re;
    double im;
};
typedef struct complex Complex;

double ComplexAbs(const Complex x);
double ComplexArg(const Complex x);
Complex ComplexAdd(const Complex x, const Complex y);
Complex ComplexSub(const Complex x, const Complex y);
Complex ComplexMul(const Complex x, const Complex y);
Complex ComplexDiv(const Complex x, const Complex y);
Complex ComplexExp(const Complex x);
Complex ComplexLog(const Complex x);
Complex ComplexNRoot(const Complex x, int n);
Complex ComplexSin(const Complex x);
Complex ComplexCos(const Complex x);
Complex ComplexTan(const Complex x);
void ComplexPrint(const Complex complex);