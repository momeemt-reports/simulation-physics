#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>

#define GENERATE_POINTS_COUNT 500
#define RAND_SEED 149
#define PI 3.14159
#define TRIAL 10

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

void generate_rand_points_in_circle (point_t *points) {
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
    generate_rand_points_in_circle(points);
    
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
    fprintf(gnu_plot, "unset key\n");
    fprintf(gnu_plot, "plot \"data.dat\"\n");
    pclose(gnu_plot);
    return 0;
}

void hit_and_miss (int count) {
    srand(RAND_SEED);
    double average_area = 0.0;
    for (int i = 0; i < TRIAL; i++) {
        int hit = 0;
        for (int j = 0; j < count; j++) {
            point_t point = rand_point();
            if (pow(point.x, 2) + pow(point.y, 2) <= 1.0) {
                hit++;
            }
        }
        average_area += (double)hit / (double)count / (double)TRIAL * 4.0;
    }
    printf("-------------点の数: %d-------------\n", count);
    printf("面積の平均値(10試行): %f\n", average_area);
    printf("(π-面積の平均値)/π: %f\n", (PI - average_area) / PI);
}

int main () {
    hit_and_miss(100);
    hit_and_miss(1000);
    hit_and_miss(10000);
    return 0;
}
