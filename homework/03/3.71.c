#include <stdio.h>
#include <string.h>

#define N 10

char buffer[N];

int good_echo() {
    while (fgets(buffer, N, stdin) != NULL) {
        printf("%s", buffer);
        if (buffer[strlen(buffer) - 1] == '\n') {
            break;
        }
    }
    if (feof(stdin))
        return EOF;
    if (ferror(stdin))
        return 1;
    return 0;
}

int main() {
    printf("%d\n", good_echo());
}
