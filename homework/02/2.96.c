#include <assert.h>
#include <limits.h>
#include <stdio.h>

/* Access bit-level representation floating-point number */
typedef unsigned float_bits;

/*
* Compute (int) f.
* If conversion causes overflow or f is NaN, return 0x80000000
*/
int float_f2i(float_bits f) {
    unsigned sign = f >> 31;
    unsigned exp = (f >> 23) & 0xFF;
    unsigned frac = f & 0x7FFFFF;

    if (exp == 0xFF) {
        // INF or NaN.
        return INT_MIN;
    }
    if (exp > 0) {
        // Implicit 1.
        frac |= 1 << 23;
    }
    // Make exponet 0 by shifting.
    unsigned bias = 0x7F;
    for (; exp < bias + 23; ++exp) {
        frac >>= 1;
    }
    for (; exp > bias + 23; --exp) {
        frac <<= 1;
        if (frac & INT_MIN) {
            // This will include overflow and INT_MIN,
            // but it's fine to just return INT_MIN.
            return INT_MIN;
        }
    }
    return sign ? -frac : frac;
}

float u2f(unsigned x) {
    return *(float *)&x;
}

int check(unsigned x) {
    int expected_value = (int)u2f(x);
    int computed_value = float_f2i(x);
    if (expected_value != computed_value) {
        printf("%u %d %d\n", x, expected_value, computed_value);
    }
    return expected_value == computed_value;
}

int main() {
    unsigned x = 0;
    do {
        assert(check(x));
        x += 1;
    } while (x);
}
