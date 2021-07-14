#include <assert.h>
#include <limits.h>

int fits_bits(int x, int n) {
    int w = sizeof(int) << 3;
    return (x << (w - n) >> (w - n)) == x;
}

int main() {
    assert(fits_bits(0, 1) == 1);
    assert(fits_bits(1, 1) == 0);
    assert(fits_bits(1, 2) == 1);
    assert(fits_bits(-1, 1) == 1);
    assert(fits_bits(2, 2) == 0);
    assert(fits_bits(2, 3) == 1);
}
