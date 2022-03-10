#include <stdio.h>
#include <stdlib.h>
#include "matrix.h"
struct MutiFunction
{ 
    unsigned int inputDim;
    unsigned int outputDim;
    void *(*function)(Matrix *x, Matrix *y);
};
typedef struct MutiFunction MutiFunction;
Matrix *mutifunctionCall(MutiFunction *function, Matrix *x);