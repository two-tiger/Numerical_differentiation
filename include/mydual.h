#pragma once

struct mydual
{
    double re;
    double du;
};
typedef struct mydual Dual;

double DualAbs(const Dual x);
Dual DualCon(const Dual x);
Dual DualInv(const Dual x);
Dual DualAdd(const Dual x, const Dual y);
Dual DualSub(const Dual x, const Dual y);
Dual DualMul(const Dual x, const Dual y);
Dual DualDiv(const Dual x, const Dual y);
Dual DualExp(const Dual x);
Dual DualLog(const Dual x);
Dual DualSin(const Dual x);
Dual DualCos(const Dual x);
Dual DualTan(const Dual x);
void DualPrint(const Dual dual);
