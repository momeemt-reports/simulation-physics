#include "hit_miss.h"

int main () {
    // 課題①
    if (make_circle_graph()) {
        return 1;
    }
    // 課題②
    hit_and_miss(100);
    hit_and_miss(1000);
    hit_and_miss(10000);
    return 0;
}
