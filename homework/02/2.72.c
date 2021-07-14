#include <string.h>

// A. Because sizeof returns a unsigned integer,
// the left hand side of ">=" will be converted to unsigned integer.
// So the condition of if statement is always true.

void copy_int(int val, void *buf, int maxbytes) {
    if ((size_t)maxbytes >= sizeof(val))
        memcpy(buf, (void *) &val, sizeof(val));
}

int main() {
}
