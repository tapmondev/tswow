#ifndef LIBTOMCRYPT_ALLOC_H
#define LIBTOMCRYPT_ALLOC_H

#include <stdlib.h>
#include <string.h>

#ifdef __cplusplus
extern "C" {
#endif

#ifdef _WIN32
  #define EXPORT __declspec(dllexport)
#else
  #define EXPORT __attribute__((visibility("default")))
#endif

EXPORT void* LibTomMalloc(size_t s);
EXPORT void* LibTomCalloc(size_t n, size_t s);
EXPORT void* LibTomRealloc(void* p, size_t s);
EXPORT void  LibTomFree(void* p);
EXPORT void  LibTomQsort(void* base, size_t nmemb, size_t size, int (*compar)(const void *, const void *));

#ifdef __cplusplus
}
#endif

#endif /* LIBTOMCRYPT_ALLOC_H */