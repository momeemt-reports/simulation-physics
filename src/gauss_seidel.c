#include "gauss_seidel.h"

double g (int x, int y) {
  return -6.0 * (double)x + 3.0 * (double)y;
}

double analytic_f (int x, int y) {
  return 3.0 * x * y * y - 1.5 * x * x * y;
}

void print_grid (double **grid, int y_len, int x_len) {
  printf("-------------------------------------------\n");
  for (int y = 0; y < y_len; y++) {
      for (int x = 0; x < x_len; x++) {
          printf("%4f ", grid[y][x]);
      }
      printf("\n");
  }
}

void copy_grid (double **src, double **dest, int y_len, int x_len) {
  for (int y = 0; y < y_len; y++) {
    for (int x = 0; x < x_len; x++) {
      dest[y][x] = src[y][x];
    }
  }
}

double **initialize_grid (int y_len, int x_len) {
  double **result = malloc(y_len * sizeof(double *));
  for (int y = 0; y < y_len; y++) {
    result[y] = malloc(x_len * sizeof(double *));
    for (int x = 0; x < x_len; x++) {
      result[y][x] = 0.0;
    }
  }
  return result;
}

void reset_grid (double **grid, int y_len, int x_len) {
  for (int y = 0; y < y_len; y++) {
    for (int x = 0; x < x_len; x++) {
      grid[y][x] = 0.0;
    }
  }
}

void free_grid (double **grid, int y_len) {
  for (int y = 0; y < y_len; y++) {
    free(grid[y]);
  }
  free(grid);
}

bool is_converged (double **arr1, double **arr2, int y_len, int x_len) {
  bool result = true;
  for (int y = 1; y < (y_len-1); y++) {
    for (int x = 1; x < (x_len-1); x++) {
      if (fabs(1.0 - arr1[y][x] / arr2[y][x]) > DBL_EPSILON) {
        result = false;
      }
    }
  }
  return result;
}

void iterative (double **src, double **dest, int y_len, int x_len, double delta_x, double(*fn)(int x, int y)) {
  for (int y = 1; y < (y_len-1); y++) {
    for (int x = 1; x < (x_len-1); x++) {
      dest[y][x] = (src[y][x+1] + src[y][x-1] + src[y+1][x] + src[y-1][x] + fn(x, y) * pow(delta_x, 2.0)) / 4.0;
    }
  }
}

void gauss_seidel (double **src, double **dest, int y_len, int x_len, double delta_x, double(*fn)(int x, int y)) {
  for (int y = 1; y < (y_len-1); y++) {
    for (int x = 1; x < (x_len-1); x++) {
      dest[y][x] = (src[y][x+1] + dest[y][x-1] + src[y+1][x] + dest[y-1][x] + fn(x, y) * pow(delta_x, 2.0)) / 4.0;
    }
  }
}

void calc_approx (double **result, double **grid, int y_len, int x_len, ApproxMethod method) {
  int trial = 0;

  while (true) {
    trial++;
    double **applied_grid = initialize_grid(y_len, x_len);

    copy_grid(grid, applied_grid, y_len, x_len);
    if (method == Iterative) {
      iterative(grid, applied_grid, y_len, x_len, 1.0, g);
    } else {
      gauss_seidel(grid, applied_grid, y_len, x_len, 1.0, g);
    }
    if (is_converged(grid, applied_grid, y_len, x_len)) {
      copy_grid(applied_grid, grid, y_len, x_len);
      free_grid(applied_grid, y_len);
      break;
    }
    copy_grid(applied_grid, grid, y_len, x_len);
    free_grid(applied_grid, y_len);
  }

  if (method == Iterative) {
    printf("反復回数（線形反復法）: %d\n", trial);
  } else {
    printf("反復回数（ガウス・ザイデル法）: %d\n", trial);
  }
  copy_grid(grid, result, y_len, x_len);
}

int assert_approx (ApproxMethod method) {
  int y_len = 4;
  int x_len = 4;
  double **result = initialize_grid(y_len, x_len);
  double **grid = initialize_grid(y_len, x_len);
  grid[1][3] = -4.5;
  grid[2][3] = 9.0;
  grid[3][1] = 22.5;
  grid[3][2] = 36.0;

  calc_approx(result, grid, y_len, x_len, method);

  int failed = 0;
  for (int y = 1; y <= 2; y++) {
    for (int x = 1; x <= 2; x++) {
      if (fabs(result[y][x] - analytic_f(x, y)) > DBL_EPSILON) {
        failed = 1;
      }
    }
  }

  free_grid(result, y_len);
  free_grid(grid, y_len);

  return failed;
}