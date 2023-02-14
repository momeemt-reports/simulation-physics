#ifndef GAUSS_SEIDEL_H
#define GAUSS_SEIDEL_H

#include <math.h>
#include <float.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

typedef enum {
  Iterative,
  GaussSeidel
} ApproxMethod;


// グリッドを出力する
void print_grid (double **grid, int y_len, int x_len);

// グリッド`src`を`dest`にコピーする
void copy_grid (double **src, double **dest, int y_len, int x_len);

// グリッドのメモリを確保して0で埋める
double **initialize_grid (int y_len, int x_len);

// グリッドのメモリを解放する
void free_grid (double **grid, int y_len);

// グリッドを全て0で埋める
void reset_grid (double **grid, int y_len, int x_len);

// グリッドの近似が終わっているかを判定する
bool is_converged (double **arr1, double **arr2, int y_len, int x_len);

// 線形反復法
void iterative (double **src, double **dest, int y_len, int x_len, double delta_x, double(*fn)(int x, int y));

// ガウス・ザイデル法
void gauss_seidel (double **src, double **dest, int y_len, int x_len, double delta_x, double(*fn)(int x, int y));

// 近似の計算
void calc_approx (double **result, double **grid, int y_len, int x_len, ApproxMethod method);

// 近似計算値が解析解と等しいか
int assert_approx (ApproxMethod method);

#endif