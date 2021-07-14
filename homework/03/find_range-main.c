#include "find_range.h"

#include <assert.h>
#include <stdio.h>

range_t find_range_reference(float x) {
    if (x < 0)
        return NEG;
    else if (x == 0)
        return ZERO;
    else if (x > 0)
        return POS;
    else
        return OTHER;
}

int check(float x) {
    int result = (find_range(x) == find_range_reference(x));
    if (!result) {
        printf("%X %f %d %d\n", *(unsigned *)&x, x, find_range(x), find_range_reference(x));
    }
    return result;
}

int main() {
    // printf("%lu\n", sizeof(range_t));
    unsigned u = 0;
    do {
        assert(check(*(float *)&u));
        u += 1;
    } while (u != 0);
    // printf("%d\n", find_range(1.0f));
}
