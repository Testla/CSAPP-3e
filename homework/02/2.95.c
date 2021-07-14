#include <assert.h>
#include <limits.h>
#include <stdio.h>

/* Access bit-level representation floating-point number */
typedef unsigned float_bits;

/* Compute 0.5*f. If f is NaN, then return f. */
float_bits float_half(float_bits f) {
    unsigned sign = f >> 31;
    unsigned exp = (f >> 23) & 0xFF;
    unsigned frac = f & 0x7FFFFF;
    if (exp == 0) {
        int needs_rounding = frac & 1;
        frac >>= 1;
        if (needs_rounding) {
            frac += frac & 1;
        }
    } else if (exp < 0xFF) {
        exp -= 1;
        if (exp == 0) {
            // Becomes denormalized.
            int needs_rounding = frac & 1;
            frac = (frac >> 1) | (1 << 22);
            if (needs_rounding) {
                frac += frac & 1;
                // Note that frac may be 1 << 23 after rounding.
                if (frac & (1 << 23)) {
                    frac ^= 1 << 23;
                    exp += 1;
                }
            }
        }
    } else {
        // INF or NaN.
        return f;
    }
    return (sign << 31) | (exp << 23) | frac;
}

float u2f(unsigned x) {
    return *(float *)&x;
}

int check(unsigned x) {
    float origin_value = u2f(x);
    if (origin_value != origin_value) {
        // NaN can't be compared.
        return 1;
    }
    // Note that type of literal 0.5 is double, using that will fail at x == 1.
    return u2f(float_half(x)) == origin_value * 0.5f;
}

int main() {
    unsigned x = 0;
    do {
        assert(check(x));
        x += 1;
    } while (x);
}
