#include <assert.h>
#include <limits.h>
#include <stdint.h>

/* Addition that saturates to TMin or TMax */
int saturating_add(int x, int y) {
    int sum = x + y;
    int w = sizeof(int) << 3;
    // If sign bits of x and y are the same,
    // while different with sign bit of result,
    // either positive or negetive overflow happended.
    // Variable overflowed's sign bit indicates whether overflow happened.
    int overflowed = ~(x ^ y) & (x ^ sum) & INT_MIN;
    int fixed_value_if_overflowed = INT_MAX ^ ((x & INT_MIN) >> (w - 1));
    // Return sum if overflow happend, fixed_value otherwise.
    return
        (sum & ~(overflowed >> (w - 1)))
        | (fixed_value_if_overflowed & (overflowed >> (w - 1)));
}

int main() {
    assert(saturating_add(0, 0) == 0);
    assert(saturating_add(INT_MAX, INT_MAX) == INT_MAX);
    assert(saturating_add(INT_MIN, INT_MIN) == INT_MIN);
}
