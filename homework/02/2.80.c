#include <assert.h>
#include <limits.h>

int divide_power2_round_up(int x, int k) {
    int w = sizeof(int) << 3;
    int sign = ((unsigned)x & INT_MIN) >> (w - 1);
    // Beware of overflow.
    // We separate x into two parts, shift and add them together.
    return (x >> k) + (((x - (x >> k << k)) + ((!sign << k) - !sign)) >> k);
}

/* Divide by power of 2. Assume 0 <= k < w-1 */
int threefourths(int x) {
    // round_down(3/4 * x)
    // = round_down(x - x / 4)
    // = x - round_up(x / 4)
    return x - divide_power2_round_up(x, 2);
}

int answer(int x) {
    return (long long)x * 3 / 4;
}

int check(int x) {
    return threefourths(x) == answer(x);
}

int main() {
    for (int x = -4; x <= 4; ++x) {
        assert(check(x));
    }
    assert(check(INT_MAX));
    assert(check(INT_MIN));
}
