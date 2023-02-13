#include <stdio.h>
#include "particle_mesh.h"

#define EXIT_IF_HAS_ERROR(x) if (x) { return 1; }

int main () {
    astronomical_body_t ab_arr[NUMBER_OF_ASTRONOMICAL_BODY];
    initialize_astronomical_bodies(ab_arr);
    for (int i = 0; i < NUMBER_OF_ASTRONOMICAL_BODY; i++) {
        print_astronomical_body(&ab_arr[i]);
    }
    return 0;
}
