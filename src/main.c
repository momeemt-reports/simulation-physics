#include <stdio.h>
#include "particle_mesh.h"

#define EXIT_IF_HAS_ERROR(x) if (x) { return 1; }

double **mass_density_map;

double rho (int x, int y) {
    return -mass_density_map[y][x];
}

int main () {
    astronomical_body_t ab_arr[NUMBER_OF_ASTRONOMICAL_BODY];
    initialize_astronomical_bodies(ab_arr);
    mass_density_map = initialize_grid(UPDATE_AREA, UPDATE_AREA);

    double **potential = initialize_grid(UPDATE_AREA, UPDATE_AREA);
    double **init_grid = initialize_grid(UPDATE_AREA, UPDATE_AREA);
    double **gravitational_field_x = initialize_grid(UPDATE_AREA, UPDATE_AREA);
    double **gravitational_field_y = initialize_grid(UPDATE_AREA, UPDATE_AREA);

    FILE *data_file = fopen("out/astronomical.dat", "w");
    if (data_file == NULL) {
        fprintf(stderr, "failed to open out/astronomical.dat.");
        return 1;
    }

    for (int nt = 0; nt < PARTICLE_MESH_TRIAL; nt++) {
        nearest_grid_point(ab_arr, mass_density_map, UPDATE_AREA, UPDATE_AREA);
        reset_grid(potential, UPDATE_AREA, UPDATE_AREA);
        gauss_seidel(init_grid, potential, UPDATE_AREA, UPDATE_AREA, 1.0, rho);

        reset_grid(gravitational_field_x, UPDATE_AREA, UPDATE_AREA);
        reset_grid(gravitational_field_y, UPDATE_AREA, UPDATE_AREA);
        for (int y = 0; y < (UPDATE_AREA-1); y++) {
            for (int x = 0; x < (UPDATE_AREA-1); x++) {
                gravitational_field_x[y][x] = -((potential[y][x+1] - potential[y][x]) / 1.0);
                gravitational_field_y[y][x] = -((potential[y+1][x] - potential[y][x]) / 1.0);
            }
        }

        for (int i = 0; i < NUMBER_OF_ASTRONOMICAL_BODY; i++) {
            int x = round(ab_arr[i].position.x);
            int y = round(ab_arr[i].position.y);
            if (0 < x && x < 100 && 0 < y && y < 100) {
                vector_t fp = {
                    MASS * gravitational_field_x[y][x],
                    MASS * gravitational_field_y[y][x]
                };
                ab_arr[i].velocity.x += (fp.x / MASS) * DT;
                ab_arr[i].velocity.y += (fp.y / MASS) * DT;
                ab_arr[i].position.x += ab_arr[i].velocity.x * DT;
                ab_arr[i].position.y += ab_arr[i].velocity.y * DT;
            }
            fprintf(data_file, "%f %f\n", ab_arr[i].position.x, ab_arr[i].position.y);
        }
    }
    fclose(data_file);

    free_grid(potential, UPDATE_AREA);
    free_grid(gravitational_field_x, UPDATE_AREA);
    free_grid(gravitational_field_y, UPDATE_AREA);
    free_grid(mass_density_map, UPDATE_AREA);


    FILE *gnu_plot = popen("gnuplot", "w");
    fprintf(gnu_plot, "set terminal gif animate delay 8 optimize\n");
    fprintf(gnu_plot, "set output \"out/astronomical.gif\"\n");
    fprintf(gnu_plot, "set xlabel \"x\"\n");
    fprintf(gnu_plot, "set ylabel \"y\"\n");
    fprintf(gnu_plot, "set size ratio 1\n");
    fprintf(gnu_plot, "unset key\n");
    fprintf(gnu_plot, "do for [i=0: 29] {\n");
    fprintf(gnu_plot, "  plot [0:100][0:100] \"out/astronomical.dat\" every ::i*500+1::(i+1)*500 using 1:2\n");
    fprintf(gnu_plot, "}\n");
    pclose(gnu_plot);

    return 0;
}
