#include "cell_automaton.h"

float rand_float (float max) {
  return max * rand() / (RAND_MAX+1.0);
}

void fill_density_array (int arr[ARR_SIZE], float density) {
  for (int i = 0; i < ARR_SIZE; i++) {
    arr[i] = (rand_float(1.0) < density);
  }
}

void print_array (int trial, int arr[ARR_SIZE]) {
  printf("trial%d: ", trial);
  for (int i = 0; i < ARR_SIZE; i++) {
    printf("%d ", arr[i]);
    if (i == (ARR_SIZE-1)) printf("\n");
  }
}

void cell_automaton_184 (int state[ARR_SIZE]) {
  int result[20];
  memcpy(result, state, sizeof(state));
  for (int i = 0; i < ARR_SIZE; i++) {
    int indexes[] = { i-1, i, i+1 };
    if (i == 0) {
      indexes[0] = ARR_SIZE-1;
    } else if (i == (ARR_SIZE-1)) {
      indexes[2] = 0;
    }
    int bit = state[indexes[0]]*4 + state[indexes[1]]*2 + state[indexes[2]];
    switch (bit) {
    case 3:
    case 4:
    case 5:
    case 7:
      result[indexes[1]] = 1;
      break;
    default:
      result[indexes[1]] = 0;
    }
  }
  memcpy(state, result, sizeof(result));
}

int run_and_output_state_to_ppm (char *dest, int state[ARR_SIZE], int ratio) {
  FILE *ppm_file = fopen(dest, "w");
  if (ppm_file == NULL) {
    fprintf(stderr, "failed to open %s.\n", dest);
    return 1;
  }
  fprintf(ppm_file, "P3\n%d %d\n255\n", 20*ratio, 21*ratio);
  for (int trial = 0; trial <= TRIAL; trial++) {
    if (trial != 0) {
      cell_automaton_184(state);
    }
    for (int y = 0; y < ratio; y++) {
      for (int i = 0; i < 20; i++) {
          int color = 0;
          if (state[i] == 0) {
              color = 255;
          }
          for (int x = 0; x < ratio; x++) {
            fprintf(ppm_file, "%d %d %d ", color, color, color);
          }
      }
      fprintf(ppm_file, "\n");
    }
  }
  fclose(ppm_file);
  return 0;
}