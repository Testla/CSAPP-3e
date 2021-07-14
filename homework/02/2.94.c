#include <assert.h>
#include <limits.h>

/* Access bit-level representation floating-point number */
typedef unsigned float_bits;

/* Compute 2*f. If f is NaN, then return f. */
float_bits float_twice(float_bits f) {
    unsigned sign = f >> 31;
    unsigned exp = (f >> 23) & 0xFF;
    unsigned frac = f & 0x7FFFFF;
    if (exp == 0) {
        frac <<= 1;
        if (frac & (1 << 23)) {
            exp += 1;
            frac ^= 1 << 23;
        }
    } else if (exp < 0xFF) {
        exp += 1;
        if (exp == 0xFF) {
            // Becomes INF.
            frac = 0;
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
        // NAN can't be compared.
        return 1;
    }
    return u2f(float_twice(x)) == origin_value * 2;
}

int main() {
    unsigned x = 0;
    do {
        assert(check(x));
        x += 1;
    } while (x);
}
