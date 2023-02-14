#include <stdio.h>

#include "particle_mesh.h"
#include "plots.h"

#define EXIT_IF_HAS_ERROR(x) if (x) { return 1; }

double **mass_density_map;

double rho (int x, int y) {
    return -mass_density_map[y][x];
}

int main () {
    srand(193);
    astronomical_body_t ab_arr[NUMBER_OF_ASTRONOMICAL_BODY];
    initialize_astronomical_bodies(ab_arr);

    FILE *f_nt0 = fopen("out/astronomical-nt0.dat", "w");
    if (f_nt0 == NULL) {
        fprintf(stderr, "failed to open out/astronomical-nt0.dat.");
        return 1;
    }
    for (int i = 0; i < NUMBER_OF_ASTRONOMICAL_BODY; i++) {
        fprintf(f_nt0, "%f %f\n", ab_arr[i].position.x, ab_arr[i].position.y);
    }
    fclose(f_nt0);

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
    FILE *f_nt10 = fopen("out/astronomical-nt10.dat", "w");
    if (f_nt10 == NULL) {
        fprintf(stderr, "failed to open out/astronomical-nt10.dat.");
        return 1;
    }
    FILE *f_nt20 = fopen("out/astronomical-nt20.dat", "w");
    if (f_nt20 == NULL) {
        fprintf(stderr, "failed to open out/astronomical-nt20.dat.");
        return 1;
    }
    FILE *f_nt30 = fopen("out/astronomical-nt30.dat", "w");
    if (f_nt30 == NULL) {
        fprintf(stderr, "failed to open out/astronomical-nt30.dat.");
        return 1;
    }      

    for (int nt = 0; nt < PARTICLE_MESH_TRIAL; nt++) {
        nearest_grid_point(ab_arr, mass_density_map, UPDATE_AREA, UPDATE_AREA);
        reset_grid(potential, UPDATE_AREA, UPDATE_AREA);

        int trial = 0;
        while (true) {
            trial++;
            double **applied_grid = initialize_grid(UPDATE_AREA, UPDATE_AREA);
            copy_grid(potential, applied_grid, UPDATE_AREA, UPDATE_AREA);
            gauss_seidel(potential, applied_grid, UPDATE_AREA, UPDATE_AREA, 1.0, rho);
            if (is_converged(potential, applied_grid, UPDATE_AREA, UPDATE_AREA) || trial > ITERATIVE_UPPER_BOUND_OF_GAUSS_ZAIDEL_METHOD) {
                copy_grid(applied_grid, potential, UPDATE_AREA, UPDATE_AREA);
                free_grid(applied_grid, UPDATE_AREA);
                break;
            }
            copy_grid(applied_grid, potential, UPDATE_AREA, UPDATE_AREA);
            free_grid(applied_grid, UPDATE_AREA);
        }

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

            if (nt == 9) {
                fprintf(f_nt10, "%f %f\n", ab_arr[i].position.x, ab_arr[i].position.y);
            } else if (nt == 19) {
                fprintf(f_nt20, "%f %f\n", ab_arr[i].position.x, ab_arr[i].position.y);
            } else if (nt == 29) {
                fprintf(f_nt30, "%f %f\n", ab_arr[i].position.x, ab_arr[i].position.y);
            }
        }
    }
    fclose(data_file);
    fclose(f_nt10);
    fclose(f_nt20);
    fclose(f_nt30);

    free_grid(potential, UPDATE_AREA);
    free_grid(gravitational_field_x, UPDATE_AREA);
    free_grid(gravitational_field_y, UPDATE_AREA);
    free_grid(mass_density_map, UPDATE_AREA);
    
    output_jpeg(
        "astronomical-nt0",
        "out/astronomical-nt0.dat",
        0, 100, 0, 100
    );
    output_jpeg(
        "astronomical-nt10",
        "out/astronomical-nt10.dat",
        0, 100, 0, 100
    );
    output_jpeg(
        "astronomical-nt20",
        "out/astronomical-nt20.dat",
        0, 100, 0, 100
    );
    output_jpeg(
        "astronomical-nt30",
        "out/astronomical-nt30.dat",
        0, 100, 0, 100
    );

    output_gif(
        "astronomical",
        "out/astronomical.dat",
        ITERATIVE_UPPER_BOUND_OF_GAUSS_ZAIDEL_METHOD,
        0, 100, 0, 100,
        NUMBER_OF_ASTRONOMICAL_BODY
    );
    return 0;
}
