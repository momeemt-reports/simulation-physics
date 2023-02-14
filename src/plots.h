#ifndef PLOTS_H
#define PLOTS_H

#include <stdio.h>

void output_jpeg (char *dest, char *input, int x0, int x1, int y0, int y1);

void output_gif (char *dest, char *input, int frame_num, int x0, int x1, int y0, int y1, int row_num);

#endif