#ifndef PARTICLE_MESH_H
#define PARTICLE_MESH_H

#include <math.h>
#include <stdio.h>
#include <stdbool.h>
#include "vectors.h"
#include "gauss_seidel.h"

#define NUMBER_OF_ASTRONOMICAL_BODY 500                  // N
#define CONSTANT_OF_GRAVITATION 1                        // G
#define MASS 1                                           // m
#define HUBBLE_CONSTANT 3.5                              // H
#define ITERATIVE_UPPER_BOUND_OF_GAUSS_ZAIDEL_METHOD 50  // ni
#define DT 0.1                                           // dt
#define PARTICLE_MESH_TRIAL 30                           // nt
#define UPDATE_AREA 101

typedef struct {
    vector_t position;
    vector_t velocity;
} astronomical_body_t;

void initialize_astronomical_bodies (astronomical_body_t astronomical_bodies[NUMBER_OF_ASTRONOMICAL_BODY]);
void print_astronomical_body (astronomical_body_t *ab);

void nearest_grid_point (
    astronomical_body_t astronomical_bodies[NUMBER_OF_ASTRONOMICAL_BODY],
    double **mass_density_map,
    int y_len, int x_len
);
void print_mass_density_map (double **mass_density_map, int y_len, int x_len);

#endif