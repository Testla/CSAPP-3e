#include <assert.h>
#include <limits.h>

// Assuming that long long is at least double the size of int.

int signed_high_prod(int x, int y) {
    long long product = (long long)x * y;
    return (int)(product >> (sizeof(int) * 8));
}

unsigned unsigned_high_prod(unsigned x, unsigned y) {
    // x' y' / 2^w
    // = (x + x_w-1 * 2^w) (y + y_w-1 * 2^w) / 2^w
    // = x y / 2^w + x_w-1 y_w-1 * 2^w + (x y_w-1 + y x_w-1)
    unsigned sign_bit_x = x >> (sizeof(int) * 8 - 1);
    unsigned sign_bit_y = y >> (sizeof(int) * 8 - 1);
    return
        signed_high_prod(x, y)
        + x * sign_bit_y
        + y * sign_bit_x;
}

unsigned unsigned_high_prod_correct(unsigned x, unsigned y) {
    unsigned long long product = (unsigned long long)x * y;
    return (unsigned)(product >> (sizeof(int) * 8));
}

int check(unsigned x, unsigned y) {
    unsigned calculated = unsigned_high_prod(x, y);
    unsigned correct = unsigned_high_prod_correct(x, y);
    return calculated == correct;
}

int main() {
    assert(check(0, 0));
    assert(check(1, 1));
    assert(check(-1, -1));
    assert(check(INT_MAX, INT_MAX));
    assert(check(INT_MIN, INT_MIN));
    assert(check(INT_MAX, INT_MIN));
}
