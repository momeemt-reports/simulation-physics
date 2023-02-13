#include "hit_miss.h"

void generate_rand_points_in_circle (vector_t *points) {
    int generated_count = 0;
    while (generated_count < GENERATE_POINTS_COUNT) {
        vector_t point = rand_vector(-1, 1);
        if (is_in_circle(&point, 1)) {
            points[generated_count] = point;
            generated_count++;
        }
    }
}

int make_circle_graph () {
    vector_t points[GENERATE_POINTS_COUNT];
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
    fprintf(gnu_plot, "set terminal jpeg\n");
    fprintf(gnu_plot, "set output \"graph.jpg\"\n");
    fprintf(gnu_plot, "set xrange [-1:1]\n");
    fprintf(gnu_plot, "set yrange [-1:1]\n");
    fprintf(gnu_plot, "set xlabel \"x\"\n");
    fprintf(gnu_plot, "set ylabel \"y\"\n");
    fprintf(gnu_plot, "set size ratio 1\n");
    fprintf(gnu_plot, "unset key\n");
    fprintf(gnu_plot, "plot \"data.dat\"\n");
    pclose(gnu_plot);
    return 0;
}

int hit_and_miss (int count) {
    srand(RAND_SEED);
    double average_area = 0.0;
    for (int i = 0; i < TRIAL; i++) {
        int hit = 0;
        for (int j = 0; j < count; j++) {
            vector_t point = rand_vector(-1, 1);
            if (pow(point.x, 2) + pow(point.y, 2) <= 1.0) {
                hit++;
            }
        }
        average_area += (double)hit / (double)count / (double)TRIAL * 4.0;
    }
    printf("-------------点の数: %d-------------\n", count);
    printf("面積の平均値(10試行): %f\n", average_area);
    printf("(π-面積の平均値)/π: %f\n", (PI - average_area) / PI);
    return 0;
}