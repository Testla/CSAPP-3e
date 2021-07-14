#include <assert.h>
#include <stdio.h>

int any_odd_one(unsigned x) {
    return !!(x & 0x55555555);
}

int main() {
    assert(any_odd_one(0) == 0);
    assert(any_odd_one(1) == 1);
    assert(any_odd_one(0xAAAAAAAA) == 0);
    assert(any_odd_one(-1) == 1);
}
