#include <stdio.h>
#include "gauss_seidel.h"

#define EXIT_IF_HAS_ERROR(x) if (x) { return 1; }

int main () {
    EXIT_IF_HAS_ERROR(assert_approx(GaussSeidel))
    return 0;
}
