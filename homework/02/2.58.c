#include <stdio.h>

int is_little_endian() {
    static short helper = 1;
    return *(unsigned char *)&helper;
}

int main() {
    printf("%d\n", is_little_endian());
}
