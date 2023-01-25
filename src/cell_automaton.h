#ifndef CELL_AUTOMATON_H
#define CELL_AUTOMATON_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define RAND_SEED 193
#define ARR_SIZE 20
#define TRIAL 20

int rand_int (int max);
void cell_automaton_184 (int state[ARR_SIZE]);
void fill_density_array (int arr[ARR_SIZE], int density);
int run_and_output_state_to_ppm (char *dest, int state[ARR_SIZE]);

#endif