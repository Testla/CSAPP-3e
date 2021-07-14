#include <assert.h>
#include <limits.h>

/* Divide by power of 2. Assume 0 <= k < w-1 */
int divide_power2(int x, int k) {
    int w = sizeof(int) << 3;
    int sign = ((unsigned)x & INT_MIN) >> (w - 1);
    // If x is negative, add (1 << k) - 1 so that it rounds towards zero.
    return (x + ((sign << k) - sign)) >> k;
}

int main() {
    assert(divide_power2(1, 1) == 0);
    assert(divide_power2(2, 1) == 1);
    assert(divide_power2(3, 1) == 1);
    assert(divide_power2(0, 1) == 0);
    assert(divide_power2(-1, 1) == 0);
    assert(divide_power2(-2, 1) == -1);
    assert(divide_power2(-3, 1) == -1);
}
