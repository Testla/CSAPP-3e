#include <assert.h>
#include <stdio.h>

int odd_ones(unsigned x) {
    x ^= x >> 1;
    x ^= x >> 2;
    x ^= x >> 4;
    x ^= x >> 8;
    x ^= x >> 16;
    return x & 1;
}

int main() {
    assert(odd_ones(0) == 0);
    assert(odd_ones(1) == 1);
    assert(odd_ones(2) == 1);
    assert(odd_ones(3) == 0);
    assert(odd_ones(0x7FFFFFFF) == 1);
    assert(odd_ones(-1) == 0);
}
