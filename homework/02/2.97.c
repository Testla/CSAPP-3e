#include <assert.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

/* Access bit-level representation floating-point number */
typedef unsigned float_bits;

/* Compute (float) i */
float_bits float_i2f(int i) {
    if (i == 0) {
        return 0;
    }

    int sign = i & INT_MIN;
    unsigned v = abs(i);
    int num_shifts_until_highest_one = 0;
    for (; (v & INT_MIN) == 0; v <<= 1)
        num_shifts_until_highest_one += 1;
    // Shifts the implicit bit out.
    v <<= 1;

    int truncated = v & 0x1FF;
    v >>= 9;
    if (truncated > 0x100 || ((truncated == 0x100) && (v & 1))) {
        v += 1;
    }
    if (v == 1 << 23) {
        // i becomes 1 << 23 after rounding,
        // after adding the carry it will become 0b10.0.
        v = 0;
        num_shifts_until_highest_one -= 1;
    }
    unsigned exponent = 0x7F + (sizeof(int) * 8 - 1 - num_shifts_until_highest_one);
    return sign | (exponent << 23) | v;
}

float u2f(unsigned x) {
    return *(float *)&x;
}

int check(int x) {
    float expected_value = (float)x;
    float computed_value = u2f(float_i2f(x));
    if (expected_value != computed_value) {
        printf("%d %f %f\n", x, expected_value, computed_value);
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
