#ifndef CELL_AUTOMATON_H
#define CELL_AUTOMATON_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define RAND_SEED 193
#define ARR_SIZE 20
#define TRIAL 20

float rand_float (float max);
void cell_automaton_184 (int state[ARR_SIZE]);
void fill_density_array (int arr[ARR_SIZE], float density);
int run_and_output_state_to_ppm (char *dest, int state[ARR_SIZE], int ratio);

#endif