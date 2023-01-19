#ifndef HIT_MISS_H
#define HIT_MISS_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>

#define GENERATE_POINTS_COUNT 500
#define RAND_SEED 193
#define PI 3.14159
#define TRIAL 10

typedef struct {
    double x;
    double y;
} point_t;

point_t rand_point ();
bool is_in_unit_circle (point_t *point);
void generate_rand_points_in_circle (point_t *points);
int make_circle_graph ();
void hit_and_miss (int count);

#endif