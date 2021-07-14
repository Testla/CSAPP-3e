#include <assert.h>
#include <limits.h>

/* Divide by power of 2. Assume 0 <= k < w-1 */
int divide_power2(int x, int k) {
    int w = sizeof(int) << 3;
    int sign = ((unsigned)x & INT_MIN) >> (w - 1);
    // If x is negative, add (1 << k) - 1 so that it rounds towards zero.
    return (x + ((sign << k) - sign)) >> k;
}

int mul3div4(int x) {
    return divide_power2(((x << 1) + x), 2);
}

int answer(int x) {
    return x * 3 / 4;
}

int check(int x) {
    return mul3div4(x) == answer(x);
}

int main() {
    for (int x = -4; x <= 4; ++x) {
        assert(check(x));
    }
    assert(check(INT_MAX));
    assert(check(INT_MIN));
}
