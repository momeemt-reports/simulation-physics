#include "cell_automaton.h"

#define EXIT_IF_HAS_ERROR(x) if (x) { return 1; }

int main () {
    srand(RAND_SEED);
    int state_30_percent[ARR_SIZE];
    int state_50_percent[ARR_SIZE];
    int state_70_percent[ARR_SIZE];
    fill_density_array(state_30_percent, 30);
    fill_density_array(state_50_percent, 50);
    fill_density_array(state_70_percent, 70);
    EXIT_IF_HAS_ERROR(run_and_output_state_to_ppm("out/30-percent.ppm", state_30_percent))
    EXIT_IF_HAS_ERROR(run_and_output_state_to_ppm("out/50-percent.ppm", state_50_percent))
    EXIT_IF_HAS_ERROR(run_and_output_state_to_ppm("out/70-percent.ppm", state_70_percent))
}
