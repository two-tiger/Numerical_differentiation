#include "myvector.h"
#include <stdlib.h>
#include "function.h"
#include <omp.h>
#include "mycomplex.h"
#include <stdio.h>
#include "mydual.h"

NdsclaFunction *NdsclaFunctionAlloc(double (*function)(Vector *), int inputsize, Complex (*complexfunction)(Vector *), Dual (*dualfunction)(Vector *))
{
    NdsclaFunction *f = (NdsclaFunction *)malloc(sizeof(NdsclaFunction));
    f->function = function;
    f->inputSize = inputsize;
    if (complexfunction != NULL)
    {
        f->complexfunction = complexfunction;
    }
    else
    {
        f->complexfunction = NULL;
    }
    if (dualfunction != NULL)
    {
        f->dualfunction = dualfunction;
    }
    else
    {
        f->dualfunction = NULL;
    }
    return f;
}

double NdsclaFunctionCall(NdsclaFunction *function, Vector *x)
{
    return function->function(x);
}

Complex NdsclaFunctionCallComplex(NdsclaFunction *function, Vector *x)
{
    return function->complexfunction(x);
}

Dual NdsclaFunctionCallDual(NdsclaFunction *function, Vector *x)
{
    return function->dualfunction(x);
}

void *NdsclaFunctionFree(NdsclaFunction *function)
{
    free(function->function);
    free(function->complexfunction);
    free(function);
}

void centralGradOMP(NdsclaFunction *function, const double h, const Vector *x0, Vector *grad)
{

    Vector *temp = VectorAlloc(x0->size);
    VectorCopy(x0, temp);
    double f_add_h, f_sub_h;
#pragma omp for
    {
        for (int i = 0; i < function->inputSize; i++)
        {
            temp->entry[i] += h;
            f_add_h = NdsclaFunctionCall(function, temp);
            temp->entry[i] -= 2 * h;
            f_sub_h = NdsclaFunctionCall(function, temp);
            temp->entry[i] += h;
            grad->entry[i] = (f_add_h - f_sub_h) / (2. * h);
        }
    }
    VectorFree(temp);
}

void centralGrad(NdsclaFunction *function, const double h, const Vector *x0, Vector *grad)
{

    Vector *temp = VectorAlloc(x0->size);
    VectorCopy(x0, temp);
    double f_add_h, f_sub_h;

    for (int i = 0; i < function->inputSize; i++)
    {
        temp->entry[i] += h;
        f_add_h = NdsclaFunctionCall(function, temp);
        temp->entry[i] -= 2 * h;
        f_sub_h = NdsclaFunctionCall(function, temp);
        temp->entry[i] += h;
        grad->entry[i] = (f_add_h - f_sub_h) / (2. * h);
    }
    VectorFree(temp);
}

void HessianMatrixOMP(NdsclaFunction *function, const Vector *x0, double h, Vector *hessian)
{
    double f_ah1_ah2, f_ah1_sh2, f_sh1_ah2, f_sh1_sh2;
#pragma omp for
    {
        for (int i = 0; i < function->inputSize; i++)
        {
            for (int j = 0; j < function->inputSize; j++)
            {
                Vector *temp = VectorAlloc(function->inputSize);
                VectorCopy(x0, temp);
                temp->entry[i] += h;
                temp->entry[j] += h;
                f_ah1_ah2 = NdsclaFunctionCall(function, temp);
                temp->entry[j] -= 2 * h;
                f_ah1_sh2 = NdsclaFunctionCall(function, temp);
                temp->entry[i] -= 2 * h;
                f_sh1_sh2 = NdsclaFunctionCall(function, temp);
                temp->entry[j] += 2 * h;
                f_sh1_ah2 = NdsclaFunctionCall(function, temp);
                hessian->entry[function->inputSize * i + j] = (f_ah1_ah2 - f_ah1_sh2 - f_sh1_ah2 + f_sh1_sh2) / (4 * h * h);
            }
        }
    }
}

void HessianMatrix(NdsclaFunction *function, const Vector *x0, double h, Vector *hessian)
{
    double f_ah1_ah2, f_ah1_sh2, f_sh1_ah2, f_sh1_sh2;
    for (int i = 0; i < function->inputSize; i++)
    {
        for (int j = 0; j < function->inputSize; j++)
        {
            Vector *temp = VectorAlloc(function->inputSize);
            VectorCopy(x0, temp);
            temp->entry[i] += h;
            temp->entry[j] += h;
            f_ah1_ah2 = NdsclaFunctionCall(function, temp);
            temp->entry[j] -= 2 * h;
            f_ah1_sh2 = NdsclaFunctionCall(function, temp);
            temp->entry[i] -= 2 * h;
            f_sh1_sh2 = NdsclaFunctionCall(function, temp);
            temp->entry[j] += 2 * h;
            f_sh1_ah2 = NdsclaFunctionCall(function, temp);
            hessian->entry[function->inputSize * i + j] = (f_ah1_ah2 - f_ah1_sh2 - f_sh1_ah2 + f_sh1_sh2) / (4 * h * h);
        }
    }
}

void bicomplexGrad(NdsclaFunction *function, const Vector *x0, double h, Vector *grad)
{
    Vector *temp = VectorAlloc(x0->size);
    VectorCopy(x0, temp);
    Complex root;
    double imroot;
    for (int i = 0; i < function->inputSize; i++)
    {
        for (int j = 0; j < function->inputSize; j++)
        {
            if (j == i)
            {
                Complex tmph = {x0->entry[j], h};
                temp->complexEntry[j] = tmph;
            }
            else
            {
                Complex tmp = {x0->entry[j], 0};
                temp->complexEntry[j] = tmp;
            }
        }
        root = NdsclaFunctionCallComplex(function, temp);
        imroot = root.im;
        grad->entry[i] = imroot / h;
    }
    VectorFree(temp);
}

void dualGrad(NdsclaFunction *function, const Vector *x0, double h, Vector *grad)
{
    Vector *temp = VectorAlloc(x0->size);
    VectorCopy(x0, temp);
    Dual root;
    double duroot;
    for (int i = 0; i < function->inputSize; i++)
    {
        for (int j = 0; j < function->inputSize; j++)
        {
            if (j == i)
            {
                Dual tmph = {x0->entry[j], h};
                temp->dualEntry[j] = tmph;
            }
            else
            {
                Dual tmp = {x0->entry[j], 0};
                temp->dualEntry[j] = tmp;
            }
        }
        root = NdsclaFunctionCallDual(function, temp);
        duroot = root.du;
        grad->entry[i] = duroot / h;
    }
    VectorFree(temp);
}