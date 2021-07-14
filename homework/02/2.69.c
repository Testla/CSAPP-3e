#include <assert.h>
#include <limits.h>

unsigned rotate_left(unsigned x, int n) {
    int w = sizeof(unsigned) << 3;
    return (x << n) | (x >> (w - n - 1) >> 1);
}

int main() {
    assert(rotate_left(0x12345678, 0) == 0x12345678);
    assert(rotate_left(0x12345678, 1) == 0x2468ACF0);
    assert(rotate_left(0x12345678, 4) == 0x23456781);
    assert(rotate_left(0x12345678, 20) == 0x67812345);
    assert(rotate_left(0x12345678, 31) == (0x12345678 >> 1));
}
