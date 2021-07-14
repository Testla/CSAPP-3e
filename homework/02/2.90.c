#include <assert.h>
#include <math.h>

float u2f(unsigned u) {
    return *(float *)&u;
}

float fpwr2(int x) {
    /* Result exponent and fraction */
    unsigned exp, frac;
    unsigned u;
    if (x < -(0x7F - 1) - 23) {
        /* Too small. Return 0.0 */
        exp = 0;
        frac = 0;
    } else if (x < -(0x7F - 1)) {
        /* Denormalized result */
        exp = 0;
        frac = 1 << (23 - -(x - -(0x7F - 1)));
    } else if (x <= 0x7F) {
        /* Normalized result. */
        exp = x + 0x7F;
        frac = 0;
    } else {
        /* Too big. Return +oo */
        exp = 0xFF;
        frac = 0;
    }
    /* Pack exp and frac into 32 bits */
    u = exp << 23 | frac;
    /* Return as float */
    return u2f(u);
}

int main() {
    for (int power = -128 - 32; power <= 128 + 1; power += 1) {
        assert(fpwr2(power) == (float)pow(2, power));
    }
}
