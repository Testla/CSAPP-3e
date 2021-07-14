#include "find_range.h"

range_t find_range(float x) {
    float zero = 0.0f;
    range_t result, temp;
    // Note that cmovb only tests if CF is true,
    // so cmovp must be after cmovb(if any).
    asm(
        "vucomiss %[z], %[x]\n\t"

        "mov $0, %[r]\n\t"

        "mov $1, %[t]\n\t"
        "cmove %[t], %[r]\n\t"

        "mov $2, %[t]\n\t"
        "cmova %[t], %[r]\n\t"

        "mov $3, %[t]\n\t"
        "cmovp %[t], %[r]\n\t"

        : [r] "=r" (result), [t] "=r" (temp)
        : [x] "x" (x), [z] "x" (zero)
    );
    return result;
}
