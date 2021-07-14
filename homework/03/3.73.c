#include "find_range.h"

range_t find_range(float x) {
    float zero = 0.0f;
    range_t result;
    // Use AssemblerTemplate "%=" to avoid conflict.
    // https://stackoverflow.com/a/16095781
    // http://gcc.gnu.org/onlinedocs/gcc/Extended-Asm.html#AssemblerTemplate
    asm(
        "vucomiss %[z], %[x]\n\t"

        "jp .other%=\n\t"
        "jb .neg%=\n\t"
        "je .zero%=\n\t"

        "mov $2, %[r]\n\t"
        "jmp .done%=\n\t"

        ".other%=:\n\t"
        "mov $3, %[r]\n\t"
        "jmp .done%=\n\t"

        ".neg%=:\n\t"
        "mov $0, %[r]\n\t"
        "jmp .done%=\n\t"

        ".zero%=:\n\t"
        "mov $1, %[r]\n\t"

        ".done%=:"
        : [r] "=r" (result)
        : [x] "x" (x), [z] "x" (zero)
    );
    return result;
}
