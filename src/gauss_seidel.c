#include "gauss_seidel.h"

double g (int x, int y) {
  return -6.0 * (double)x + 3.0 * (double)y;
}

double analytic_f (int x, int y) {
  return 3.0 * x * y * y - 1.5 * x * x * y;
}

void print_grid (double grid[4][4]) {
  printf("-------------------------------------------\n");
  for (int y = 0; y < 4; y++) {
      for (int x = 0; x < 4; x++) {
          printf("%4f ", grid[y][x]);
      }
      printf("\n");
  }
}

void copy_grid (double src[4][4], double dest[4][4]) {
  for (int y = 0; y < 4; y++) {
    for (int x = 0; x < 4; x++) {
      dest[y][x] = src[y][x];
    }
  }
}

bool is_converged (double n[4][4], double n_1[4][4]) {
  bool result = true;
  for (int y = 2; y <= 2; y++) {
    for (int x = 1; x <= 2; x++) {
      result &= fabs(1.0 - n[y][x] / n_1[y][x]) <= DBL_EPSILON;
    }
  }
  return result;
}

void iterative (double src[4][4], double dest[4][4]) {
  for (int y = 1; y <= 2; y++) {
    for (int x = 1; x <= 2; x++) {
      dest[y][x] = (src[y][x+1] + src[y][x-1] + src[y+1][x] + src[y-1][x] + g(x, y)) / 4.0;
    }
  }
}

void gauss_seidel (double src[4][4], double dest[4][4]) {
  for (int y = 1; y <= 2; y++) {
    for (int x = 1; x <= 2; x++) {
      dest[y][x] = (src[y][x+1] + dest[y][x-1] + src[y+1][x] + dest[y-1][x] + g(x, y)) / 4.0;
    }
  }
}

void calc_approx (double result[4][4], ApproxMethod method) {
  double grid[4][4] = {
    {0.0,  0.0,  0.0,  0.0},
    {0.0,  0.0,  0.0, -4.5},
    {0.0,  0.0,  0.0,  9.0},
    {0.0, 22.5, 36.0,  0.0}
  };
  int trial = 0;
  while (true) {
    trial++;
    double applied_grid[4][4] = {0};
    copy_grid(grid, applied_grid);
    if (method == Iterative) {
      iterative(grid, applied_grid);
    } else {
      gauss_seidel(grid, applied_grid);
    }
    if (is_converged(grid, applied_grid)) {
      copy_grid(applied_grid, grid);
      break;
    }
    copy_grid(applied_grid, grid);
  }
  if (method == Iterative) {
    printf("反復回数（線形反復法）: %d\n", trial);
  } else {
    printf("反復回数（ガウス・ザイデル法）: %d\n", trial);
  }
  copy_grid(grid, result);
}

int assert_approx (ApproxMethod method) {
  double result[4][4] = {};
  calc_approx(result, method);
  for (int y = 1; y <= 2; y++) {
    for (int x = 1; x <= 2; x++) {
      if (fabs(result[y][x] - analytic_f(x, y)) > DBL_EPSILON) {
        return 1;
      }
    }
  }
  return 0;
}