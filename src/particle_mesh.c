#include "particle_mesh.h"

void point_of_astronomical_body (vector_t *position) {
    while (1) {
        vector_t v = rand_vector(-5, 5);
        if (is_in_circle(&v, 5)) {
            *position = v;
            return;
        }
    }
}

vector_t velocity_of_astronomical_body (vector_t *position) {
    return multiply(position, HUBBLE_CONSTANT);
}

void initialize_astronomical_body (astronomical_body_t *ab) {
    point_of_astronomical_body(&ab->position);
    ab->velocity = velocity_of_astronomical_body(&ab->position);
    ab->position.x += 50.0;
    ab->position.y += 50.0;
}

void initialize_astronomical_bodies (astronomical_body_t astronomical_bodies[NUMBER_OF_ASTRONOMICAL_BODY]) {
    for (int i = 0; i < NUMBER_OF_ASTRONOMICAL_BODY; i++) {
        initialize_astronomical_body(&astronomical_bodies[i]);
    }
}

void print_astronomical_body (astronomical_body_t *ab) {
    printf("天体 座標: (%f, %f) 速度: (%f, %f)\n", ab->position.x, ab->position.y, ab->velocity.x, ab->velocity.y);
}

void increase (astronomical_body_t astronomical_bodies[NUMBER_OF_ASTRONOMICAL_BODY]) {
    for (int i = 0; i < NUMBER_OF_ASTRONOMICAL_BODY; i++) {
        astronomical_bodies[i].position = add(&astronomical_bodies[i].position, &astronomical_bodies[i].velocity);
    }
}

void nearest_grid_point (
    astronomical_body_t astronomical_bodies[NUMBER_OF_ASTRONOMICAL_BODY],
    double **mass_density_map,
    int y_len, int x_len
) {
    double **result = initialize_grid(y_len, x_len);
    for (int y = 0; y < y_len; y++) {
        for (int x = 0; x < x_len; x++) {
            mass_density_map[y][x] = 0.0;
        }
    }
    for (int i = 0; i < NUMBER_OF_ASTRONOMICAL_BODY; i++) {
        if (astronomical_bodies[i].position.x < 0.0 || astronomical_bodies[i].position.x > 100.0) continue;
        if (astronomical_bodies[i].position.y < 0.0 || astronomical_bodies[i].position.y > 100.0) continue;
        int x = round(astronomical_bodies[i].position.x);
        int y = round(astronomical_bodies[i].position.y);
        mass_density_map[y][x] += 1.0;
    }
    free_grid(result, y_len);
}

void print_mass_density_map (double **mass_density_map, int y_len, int x_len) {
    for (int y = 0; y < y_len; y++) {
        for (int x = 0; x < x_len; x++) {
            printf("%2d ", (int)mass_density_map[y][x]);
        }
        printf("\n");
    }
}