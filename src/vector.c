#include <stdlib.h>
#include <myvector.h>

Vector *vector_alloc(int size)
{
    Vector *v = malloc(sizeof(Vector));
    v->entry = malloc(sizeof(double) * size);
    v->size = size;
};

int vector_free(Vector *v)
{
    free(v->entry);
    free(v);
}

void vector_copy(Vector *v, Vector *w)
{
    for (size_t i = 0; i < v->size; i++)
    {
        w->entry[i] = v->entry[i];
    }
}

Vector *vector_add_const(Vector *v, float a, int copy)
{
    // add a const to a vector
    if (copy == 1)
    {
        Vector *w = vector_alloc(v->size);
        vector_copy(v, w);
        for (size_t i = 0; i < v->size; i++)
        {
            w->entry[i] = v->entry[i] + a;
        }
    }
    else
    {
        for (size_t i = 0; i < v->size; i++)
        {
            v->entry[i] += a;
        }
    }
}

Vector *vector_add_vector(Vector *v, Vector *w, int copy)
{
    // add a const to a vector
    if (copy == 1)
    {
        Vector *u = vector_alloc(v->size);
        for (size_t i = 0; i < v->size; i++)
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
