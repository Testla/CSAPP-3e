#include <assert.h>
#include <limits.h>

int lower_one_mask(int n) {
    return (((1 << (n - 1)) - 1) << 1) + 1;
}

int main() {
    assert(lower_one_mask(1) == 1);
    assert(lower_one_mask(2) == 3);
    assert(lower_one_mask(6) == 0x3F);
    assert(lower_one_mask(17) == 0x1FFFF);
    assert(lower_one_mask(31) == INT_MAX);
    assert(lower_one_mask(32) == -1);
}
