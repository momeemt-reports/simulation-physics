#include "vectors.h"

vector_t add (vector_t *v1, vector_t *v2) {
    vector_t v;
    v.x = v1->x + v2->x;
    v.y = v1->y + v2->y;
    return v;
}

vector_t multiply (vector_t *v1, double scalar) {
    vector_t v;
    v.x = v1->x * scalar;
    v.y = v1->y * scalar;
    return v;
}

vector_t subtract (vector_t *v1, vector_t *v2) {
    vector_t minus_v1 = multiply(&v1, -1);
    return add(&minus_v1, &v2);
}

double rand_double (double start, double end) {
  return (fabs(end - start) * rand()) / (RAND_MAX + 1.0) + start;
};

vector_t rand_vector (double start, double end) {
    vector_t v;
    v.x = rand_double(start, end);
    v.y = rand_double(start, end);
    return v;
}

bool is_in_circle (vector_t *point, double r) {
    return pow(point->x, 2) + pow(point->y, 2) <= r*r;
}