#include <assert.h>
#include <stdio.h>

// Avoid using ~0xFF because we don't know the type of y.
#define f(x, y) ((x & 0xFF) | (y ^ (y & 0xFF)))

int main() {
    assert(f(0x89ABCDEF, 0x76543210) == 0x765432EF);
}
