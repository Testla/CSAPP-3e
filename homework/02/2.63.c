#include <assert.h>
#include <stdio.h>

unsigned srl(unsigned x, int k) {
    /* Perform shift arithmetically */
    // I don't know why but the above comment from the book is wrong.
    unsigned xsra = (int) x >> k;
    // Keep only the lower (w - k) bits.
    // We may shift w bits if k == 0, so we calculate it by two steps.
    int shift_amount = (sizeof(int) << 3) - k;
    int mask = (((1 << (shift_amount - 1)) - 1) << 1) + 1;
    return xsra & mask;
}

int sra(int x, int k) {
    /* Perform shift logically */
    int xsrl = (unsigned) x >> k;
    int shift_amount = (sizeof(int) << 3) - k - 1;
    // The original sign bit is at 1 << shift_amount after shifting right.
    int original_sign_bit = xsrl & (1 << shift_amount);
    int mask = ~(((original_sign_bit - 1) << 1) + 1);
    return xsrl ^ mask;
}

int main() {
    static const int Max_shift = (sizeof(int) << 3) - 1;

    assert(srl(0, 0) == 0);
    assert(srl(0, 1) == 0);
    assert(srl(0, Max_shift) == 0);
    assert(srl(~0, 0) == (unsigned)~0);
    assert(srl(~0, 1) == (unsigned)~0 >> 1);
    assert(srl(~0, Max_shift) == (unsigned)~0 >> Max_shift);

    assert(sra(0, 0) == 0);
    assert(sra(0, 1) == 0);
    assert(sra(0, Max_shift) == 0);
    assert(sra(~0, 0) == ~0);
    assert(sra(~0, 1) == ~0 >> 1);
    assert(sra(~0, Max_shift) == ~0 >> Max_shift);
}
