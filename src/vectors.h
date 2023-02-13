#ifndef VECTORS_H
#define VECTORS_H

#include <math.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct {
    double x;
    double y;
} vector_t;

vector_t add (vector_t *v1, vector_t *v2);
vector_t subtract (vector_t *v1, vector_t *v2);
vector_t multiply (vector_t *v1, double scalar);
vector_t rand_vector (double start, double end);
double rand_double (double start, double end);
vector_t rand_vector (double start, double end);
bool is_in_circle (vector_t *point, double r);

#endif