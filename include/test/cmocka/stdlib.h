#ifndef _CMOCKA_TEST_CMOCKA_STDLIB_H_
#define _CMOCKA_TEST_CMOCKA_STDLIB_H_
#ifdef TEST

#include <stddef.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

void *cmocka_test_malloc(size_t size, const char *file, int line);

#define malloc(size) cmocka_test_malloc(size, __FILE__, __LINE__)
extern _Thread_local bool malloc_is_overridden;

void *cmocka_test_calloc(size_t nmemb, size_t size, const char *file, int line);

#define calloc(nmemb, size) cmocka_test_calloc(nmemb, size, __FILE__, __LINE__)
extern _Thread_local bool calloc_is_overridden;

void *cmocka_test_realloc(void *ptr, size_t size, const char *file, int line);

#define realloc(ptr, size) cmocka_test_realloc(ptr, size, __FILE__, __LINE__)
extern _Thread_local bool realloc_is_overridden;

void cmocka_test_free(void *ptr, const char *file, int line);

#define free(ptr) cmocka_test_free(ptr, __FILE__, __LINE__)

void cmocka_test_abort(const char *file, int line);

#define abort() cmocka_test_abort(__FILE__, __LINE__)
extern _Thread_local bool abort_is_overridden;

int cmocka_test_posix_memalign(void **out, size_t alignment, size_t size,
                               const char *file, int line);
#define posix_memalign(out, alignment, size) \
    cmocka_test_posix_memalign(out, alignment, size, __FILE__, __LINE__)
extern _Thread_local bool posix_memalign_is_overridden;

#endif /* TEST */
#endif /* _CMOCKA_TEST_CMOCKA_STDLIB_H_ */
