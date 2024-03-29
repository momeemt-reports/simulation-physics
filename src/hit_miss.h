#ifndef HIT_MISS_H
#define HIT_MISS_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>
#include "vectors.h"

#define GENERATE_POINTS_COUNT 500
#define RAND_SEED 193
#define PI 3.14159
#define TRIAL 10

void generate_rand_points_in_circle (vector_t *points);
int make_circle_graph ();
int hit_and_miss (int count);

#endif