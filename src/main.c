#include "hit_miss.h"

#define EXIT_IF_HAS_ERROR(x) if (x) { return 1; }

int main () {
    // 課題①
    EXIT_IF_HAS_ERROR(make_circle_graph())
    // 課題②
    EXIT_IF_HAS_ERROR(hit_and_miss(100))
    EXIT_IF_HAS_ERROR(hit_and_miss(1000))
    EXIT_IF_HAS_ERROR(hit_and_miss(10000))
    return 0;
}
