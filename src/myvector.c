#include <stdlib.h>
#include <stdio.h>
#include "myvector.h"

Vector *VectorAlloc(int size)
{
    Vector *v = (Vector *)malloc(sizeof(Vector));
    v->entry = (double *)malloc(sizeof(double) * size);
    v->complexEntry = (Complex *)malloc(sizeof(Complex) * size);
    v->dualEntry = (Dual *)malloc(sizeof(Dual) * size);
    v->size = size;
    return v;
};

void *VectorFree(Vector *v)
{
    free(v->dualEntry);
    free(v->complexEntry);
    free(v->entry);
    free(v);
}

void VectorCopy(const Vector *v, Vector *w)
{
    if (v->size != w->size)
    {
        printf("VectorCopy: w and v must have the same size");
        exit(-1);
    }

    for (int i = 0; i < v->size; i++)
    {
        w->entry[i] = v->entry[i];
    }
    w->size = v->size;
}

Vector *VectorAddConst(Vector *v, double a, int copy)
{
    if (copy == 1)
    {
        Vector *w = VectorAlloc(v->size);
        VectorCopy(v, w);
        for (int i = 0; i < v->size; i++)
        {
            w->entry[i] += a;
        }
        return w;
    }

    for (int i = 0; i < v->size; i++)
    {
        v->entry[i] += a;
    }
    return v;
}

Vector *VectorAddVector(Vector *v, Vector *w, int copy)
{
    if (v->size != w->size)
    {
        printf("v and w must have the same size");
        exit(-1);
    }
    if (copy == 1)
    {
        Vector *u = VectorAlloc(v->size);
        for (int i = 0; i < u->size; i++)
        {
            u->entry[i] = v->entry[i] + w->entry[i];
        }
        return u;
    }
    else
    {
        for (int i = 0; i < v->size; i++)
        {
            w->entry[i] += v->entry[i];
        }
        return w;
    }
}

Vector *VectorMultiply(Vector *v, double a, int copy)
{
    if (copy == 1)
    {
        Vector *w = VectorAlloc(v->size);
        for (int i = 0; i < v->size; i++)
        {
            w->entry[i] = v->entry[i] * a;
        }
        return w;
    }
    else
    {
        for (int i = 0; i < v->size; i++)
        {
            v->entry[i] *= a;
        }
        return v;
    }
}

void *VectorPrint(Vector *v)
{
    printf("[");
    for (int i = 0; i < v->size; i++)
    {
        printf("%f, ", v->entry[i]);
    }
    printf("]");
}

Matrix *MatrixAlloc(int rowSize, int colSize)
{
    Matrix *m = (Matrix *)malloc(sizeof(Matrix));
    m->grad = (Vector **)malloc(sizeof(Vector *) * rowSize);
    for (int i = 0; i < rowSize; i++)
    {
        m->grad[i] = VectorAlloc(colSize);
    }
    m->rowSize = rowSize;
    return m;
}

void *MatrixFree(Matrix *m)
{
    free(m->grad);
    free(m);
}

void *MatrixPrint(Matrix *m)
{
    printf("[");
    for (int i = 0; i < m->rowSize; i++)
    {
        for (int j = 0; j < m->grad[i]->size; j++)
        {
            printf("%f, ", m->grad[i]->entry[j]);
        }
        printf("\n");
    }
    printf("]");
}

void *HessianPrint(Vector *H, int inputsize, int outputsize)
{
    printf("[");
    for (int i = 0; i < outputsize; i++)
    {
        for (int j = 0; j < inputsize; j++)
        {
            printf("%f, ", H->entry[outputsize * i + j]);
        }
        printf("\n");
    }
    printf("]");
}