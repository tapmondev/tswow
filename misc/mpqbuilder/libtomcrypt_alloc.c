#include "libtomcrypt_alloc.h"

void* LibTomMalloc(size_t s) { return malloc(s); }
void* LibTomCalloc(size_t n, size_t s) { return calloc(n, s); }
void* LibTomRealloc(void* p, size_t s) { return realloc(p, s); }
void  LibTomFree(void* p)    { free(p); }
void  LibTomQsort(void* base, size_t nmemb, size_t size, int (*compar)(const void *, const void *)) {
    qsort(base, nmemb, size, compar);
}
