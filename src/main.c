#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>

#define GENERATE_POINTS_COUNT 500
#define RAND_SEED 149

typedef struct {
    double x;
    double y;
} point_t;

double rand_double () {
    return (2.0 * rand()) / (RAND_MAX + 1.0) - 1.0;
}

point_t rand_point () {
    point_t point;
    point.x = rand_double();
    point.y = rand_double();
    return point;
}

bool is_in_unit_circle (point_t *point) {
    return pow(point->x, 2) + pow(point->y, 2) <= 1;
}

void generate_rand_points (point_t *points) {
    int generated_count = 0;
    while (generated_count < GENERATE_POINTS_COUNT) {
        point_t point = rand_point();
        if (is_in_unit_circle(&point)) {
            points[generated_count] = point;
            generated_count++;
        }
    }
}

int make_circle_graph () {
    point_t points[GENERATE_POINTS_COUNT];
    srand(RAND_SEED);
    generate_rand_points(points);
    
    FILE *data_file = fopen("data.dat", "w");
    if (data_file == NULL) {
        fprintf(stderr, "failed to open data.dat.");
        return 1;
    }
    for (int i = 0; i < GENERATE_POINTS_COUNT; i++) {
        fprintf(data_file, "%f %f\n", points[i].x, points[i].y);
    }

    FILE *gnu_plot = popen("gnuplot", "w");
    fprintf(gnu_plot, "set terminal png\n");
    fprintf(gnu_plot, "set output \"graph.png\"\n");
    fprintf(gnu_plot, "set xrange [-1:1]\n");
    fprintf(gnu_plot, "set yrange [-1:1]\n");
    fprintf(gnu_plot, "set size ratio 1\n");
    fprintf(gnu_plot, "plot \"data.dat\"\n");
    pclose(gnu_plot);
    return 0;
}

int main () {
    return make_circle_graph();
}
