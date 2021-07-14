#include <assert.h>
#include <limits.h>
#include <stdio.h>

int main() {
    int x, y;
    unsigned ux, uy;

    // A.
    x = INT_MIN, y = 0;
    // I don't know why but seems -x is positive when running.
    // printf("%d\n", -x > INT_MAX);
    // assert(((x < y) == (-x > -y)) == 0);

    // B. True. Left shift by 4 equal multiply by 16.
    // Also addition and multiplication are associative and commutative.

    // C. True.
    // ~x + ~y + 1
    // = (-x - 1) + (-y - 1) - 1
    // = -(x + y) - 1
    // = ~(x + y) + 1 - 1
    // = ~(x + y)

    // D. True. The bit representation are the same.

    // E. True. The lowest two bits will be set to zero.
}
