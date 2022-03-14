#pragma once
struct myvector
{
    int size;
    double *entry;
};
typedef struct myvector Vector;

struct mymatrix
{
    int rowSize;
    Vector **grad;
};
typedef struct mymatrix Matrix;

Vector *VectorAlloc(int size);
void *VectorFree(Vector *v);
void VectorCopy(const Vector *v, Vector *w);
Vector *VectorAddConst(Vector *v, double a, int copy);
Vector *VectorAddVector(Vector *v, Vector *w, int copy);
Vector *VectorMultiply(Vector *v, double a, int copy);
void *VectorPrint(Vector *v);
Matrix *MatrixAlloc(int rowSize, int colSize);
void *MatrixFree(Matrix *m);
void *MatrixPrint(Matrix *m);