#include <assert.h>
#include <stdio.h>

int int_shifts_are_arithmetic() {
    // If right shift is arithmetic,
    // right-shifting ~0 by no more than (w - 1) bits always result in ~0.
    return !((~0 >> 1) ^ ~0);
}

int main() {
    assert(int_shifts_are_arithmetic());
}
