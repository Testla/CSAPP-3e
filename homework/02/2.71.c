#include <assert.h>
#include <limits.h>

// A. The sign bit of the result is always 0.

/* Declaration of data type where 4 bytes are packed
into an unsigned */
typedef unsigned packed_t;
/* Extract byte from word. Return as signed integer */
int xbyte(packed_t word, int bytenum) {
    return (int)(word << ((3 - bytenum) << 3)) >> (3 << 3);
}

int main() {
    assert(xbyte(0x80008001, 0) == (char)1);
    assert(xbyte(0x80008001, 1) == (char)0x80);
    assert(xbyte(0x80008001, 2) == (char)0);
    assert(xbyte(0x80008001, 3) == (char)0x80);
}
