#include <stdlib.h>
#include <stdio.h>
#include "myvector.h"

Vector *VectorAlloc(int size)
{
    Vector *v = (Vector *)malloc(sizeof(Vector));
    v->entry = (double *)malloc(sizeof(double) * size);
    v->size = size;
    return v;
};

void *VectorFree(Vector *v)
{
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

    for (size_t i = 0; i < v->size; i++)
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
        for (size_t i = 0; i < v->size; i++)
        {
            w->entry[i] += a;
        }
        return w;
    }

    for (size_t i = 0; i < v->size; i++)
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
        for (size_t i = 0; i < u->size; i++)
        {
            u->entry[i] = v->entry[i] + w->entry[i];
        }
        return u;
    }
    else
    {
        for (size_t i = 0; i < v->size; i++)
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
        for (size_t i = 0; i < v->size; i++)
        {
            w->entry[i] = v->entry[i] * a;
        }
        return w;
    }
    else
    {
        for (size_t i = 0; i < v->size; i++)
        {
            v->entry[i] *= a;
        }
        return v;
    }
}

void *VectorPrint(Vector *v)
{
    printf("[");
    for (size_t i = 0; i < v->size; i++)
    {
        printf("%f, ", v->entry[i]);
    }
    printf("]");
}

Matrix *MatrixAlloc(int rowSize)
{
    Matrix *m = (Matrix *)malloc(sizeof(Matrix));
    m->grad = (Vector *)VectorAlloc(sizeof(Vector) * rowSize);
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
    for (size_t i = 0; i < m->rowSize; i++)
    {
        for (size_t j = 0; j < m->grad->size; j++)
        {
            printf("%f, ", m->grad->entry[j]);
        }
        printf("\n");
    }
    printf("]");
}