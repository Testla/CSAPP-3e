#include <assert.h>
#include <limits.h>

/* Determine whether arguments can be subtracted without overflow */
int tsub_ok(int x, int y) {
    int delta = x - y;
    if (y == INT_MIN)
        return delta >= 0;
    return
        !((x >= 0 && -y >= 0 && delta < 0)
          || (x < 0 && -y < 0 && delta >= 0));
}

int main() {
    assert(tsub_ok(0, INT_MIN) == 0);
    assert(tsub_ok(-1, INT_MIN) == 1);
    assert(tsub_ok(-1, INT_MAX) == 1);
    assert(tsub_ok(-2, INT_MAX) == 0);
}
