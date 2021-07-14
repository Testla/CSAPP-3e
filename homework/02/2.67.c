#include <assert.h>
#include <limits.h>

// A: The amount of shifting should be less than width of the left operand.

int int_size_is_32() {
    return ((unsigned)INT_MIN >> 15 >> 15 >> 1) == 1;
}

int main() {
    assert(int_size_is_32() == 1);
}
