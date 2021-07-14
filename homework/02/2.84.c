#include <assert.h>
#include <limits.h>
#include <stdio.h>

unsigned f2u(float x) {
    return *(unsigned *)&x;
}

int float_le(float x, float y) {
    unsigned ux = f2u(x);
    unsigned uy = f2u(y);
    /* Get the sign bits */
    unsigned sx = ux >> 31;
    unsigned sy = uy >> 31;
    /* Give an expression using only ux, uy, sx, and sy */
    return
        (sx > sy)
        || (sx == sy
            && ((sx == 1 && ux >= uy)
                || (sx == 0 && ux <= uy)));
}

int check(float x, float y) {
    return (x <= y) == float_le(x, y);
}

int main() {
    for (float x = -2; x <= 2; x += 1)
        for (float y = -2; y <= 2; y += 1)
            assert(check(x, y));
}
