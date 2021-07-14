#include <assert.h>
#include <limits.h>
#include <math.h>

/* Access bit-level representation floating-point number */
typedef unsigned float_bits;

/* Compute |f|. If f is NaN, then return f. */
float_bits float_absval(float_bits f) {
    unsigned exp = (f >> 23) & 0xFF;
    unsigned frac = f & 0x7FFFFF;
    if (exp == 0xFF && frac != 0) {
        return f;
    }
    return f & INT_MAX;
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
    return u2f(float_absval(x)) == fabsf(origin_value);
}

int main() {
    unsigned x = 0;
    do {
        assert(check(x));
        x += 1;
    } while (x);
}
