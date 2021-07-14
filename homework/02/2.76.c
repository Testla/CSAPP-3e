#include <assert.h>
#include <stdlib.h>
#include <string.h>

void *calloc(size_t nmemb, size_t size) {
    if (!(nmemb && size))
        return NULL;
    size_t total_size = nmemb * size;
    if (total_size / nmemb != size)
        return NULL;
    void *mem = malloc(total_size);
    if (mem == NULL)
        return NULL;
    memset(mem, '\0', total_size);
    return mem;
}

int main() {
    assert(calloc(0, 1) == NULL);
    assert(calloc(1, 0) == NULL);
    void *mem = calloc(1, 1);
    assert(mem != NULL);
    assert((((char *)mem)[0]) == '\0');
    free(mem);
}
