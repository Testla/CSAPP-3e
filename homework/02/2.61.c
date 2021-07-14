#include <assert.h>
#include <stdio.h>

int a(int x) {
    // Two ! simply turns any non-zero number into 1.
    return !!x;
}

int b(int x) {
    return !!~x;
}

int c(int x) {
    return !!(x & 0xFF);
}

int d(int x) {
    // If all bits in the most significant byte equal 1,
    // then shifting that byte to least significant place results in ~0.
    return !!((x >> ((sizeof(int) - 1) * 8)) ^ ~0);
}

int main() {
    int x;

    x = 0;
    assert(a(x) == 0);
    assert(b(x) == 1);
    assert(c(x) == 0);
    assert(d(x) == 1);

    x = ~0;
    assert(a(x) == 1);
    assert(b(x) == 0);
    assert(c(x) == 1);
    assert(d(x) == 0);

    x = 0xFF;
    assert(a(x) == 1);
    assert(b(x) == 1);
    assert(c(x) == 1);
    assert(d(x) == 1);

    x = 0x0F;
    assert(a(x) == 1);
    assert(b(x) == 1);
    assert(c(x) == 1);
    assert(d(x) == 1);

    x = 0xFF000000;
    assert(a(x) == 1);
    assert(b(x) == 1);
    assert(c(x) == 0);
    assert(d(x) == 0);

    x = 0xF0000000;
    assert(a(x) == 1);
    assert(b(x) == 1);
    assert(c(x) == 0);
    assert(d(x) == 1);
}
