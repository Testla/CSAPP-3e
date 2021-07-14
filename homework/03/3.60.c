/*
A. x in rdi, n in esi and ecx, result in rax, mask in rdx.
B. result is 0 and mask is 1.
C. mask != 0.
D. mask = mask << n.
E. result |= x & mask.
*/

long loop(long x, long n) {
    long result = 0;
    long mask;
    for (mask = 1; mask != 0; mask = mask << n) {
        result |= x & mask;
    }
    return result;
}
