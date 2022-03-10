#include "VectorFunction.h"

Matrix *mutifunctionCall(MutiFunction *function, Matrix *x)
{
    if (x->col_size != 1)
        terminate("ERROR: mutifunction must called with a column vector");
    if (x->row_size != function->inputDim)
        terminate("ERROT: inputsize != function.inputsize");
    Matrix *ans = matrix_alloc(function->outputDim, 1);
    function->function(x, ans);
    return ans;
}