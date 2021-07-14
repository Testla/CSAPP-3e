#include <assert.h>
#include <limits.h>

int A(int k) {
    // Shift two times in case of k == 32.
    return UINT_MAX << (k & 0x1F) << ((k & 0x20) >> 1) << ((k & 0x20) >> 1);
}

int B(int k, int j) {
    // Generate k ones, then shift it left.
    return ~A(k) << j;
}

int main() {
    assert(A(0) == -1);
    assert(A(1) == -2);
    assert(A(16) == (int)0xFFFF0000);
    assert(A(32) == 0);
    assert(B(0, 0) == 0);
    assert(B(4, 4) == 0xF0);
    assert(B(16, 16) == (int)0xFFFF0000);
    assert(B(32, 0) == -1);
    assert(B(0, 32) == 0);
}
