#include "cell_automaton.h"

#define EXIT_IF_HAS_ERROR(x) if (x) { return 1; }

int suite (int seed) {
    srand(seed);
    int percents[3] = { 30, 50, 70 };
    for (int i = 0; i < 3; i++) {
        int state[ARR_SIZE];
        fill_density_array(state, (float)percents[i] / 100);
        char path[27];
        sprintf(path, "out/%d-percent-seed-%d.ppm", percents[i], seed);
        EXIT_IF_HAS_ERROR(run_and_output_state_to_ppm(path, state, 25))
    }
    return 0;
}

int main () {
    int seeds[5] = { 149, 193, 251, 383, 457 };
    for (int i = 0; i < 5; i++) {
        EXIT_IF_HAS_ERROR(suite(seeds[i]))
    }
    return 0;
}
