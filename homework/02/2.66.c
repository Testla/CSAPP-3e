#include <assert.h>
#include <limits.h>
#include <stdio.h>

int leftmost_one(unsigned x) {
    // Turn every bit to the right of the leftmost one to one.
    x |= x >> 1;
    x |= x >> 2;
    x |= x >> 4;
    x |= x >> 8;
    x |= x >> 16;
    // Remove all ones that are not the leftmost one.
    return x ^ (x >> 1);
}

int main() {
    assert(leftmost_one(0) == 0);
    assert(leftmost_one(1) == 1);
    assert(leftmost_one(2) == 2);
    assert(leftmost_one(3) == 2);
    assert(leftmost_one(0x7FFFFFFF) == 0x40000000);
    assert(leftmost_one(-1) == INT_MIN);
}
