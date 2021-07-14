#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int rand_int() {
    // Generate random number in whole int range.
    // Assumes RAND_MAX is INT_MAX.
    return rand() ^ ((rand() & 1) << (sizeof(int) * 8 - 1));
}

void show_double(double x) {
    unsigned char *ptr = (unsigned char *)&x;
    for (unsigned i = 0; i < sizeof(double); ++i) {
        printf("%02X", ptr[i]);
    }
}

void print_double(double x) {
    printf("%.0lf ", x);
    show_double(x);
    puts("");
}

int main() {
    // printf("RAND_MAX is %d\n", RAND_MAX);
    srand(time(NULL));
    int count = 0;
    for (int i = 0; i < 100; ++i) {
        // int x = rand_int(), y = rand_int(), z = rand_int();
        int x = rand(), y = rand(), z = rand();
        double dx = x, dy = y, dz = z;
        double exp1 = (dx * dy) * dz;
        double exp2 = dx * (dy * dz);
        if (exp1 != exp2) {
            count += 1;
            printf("x, y, z = %d, %d, %d\n", x, y, z);
            // print_double(dx * dy);
            // print_double(exp1);
            // print_double(dy * dz);
            // print_double(exp2);
            printf("dxdy = %.0lf\n", dx * dy);
            printf("exp1 = %.0lf\n", exp1);
            printf("dydz = %.0lf\n", dy * dz);
            printf("exp2 = %.0lf\n", exp2);
        }
    }
    printf("%d\n", count);
}
