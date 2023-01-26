#ifndef GAUSS_SEIDEL_H
#define GAUSS_SEIDEL_H

#include <math.h>
#include <float.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

typedef enum {
  Iterative,
  GaussSeidel
} ApproxMethod;

void print_grid (double grid[4][4]);

// 線形反復法
void iterative (double src[4][4], double dest[4][4]);

// ガウス・ザイデル法
void gauss_seidel (double src[4][4], double dest[4][4]);

// 近似の計算
void calc_approx (double result[4][4], ApproxMethod method);

// 近似計算値が解析解と等しいか
int assert_approx (ApproxMethod method);

#endif