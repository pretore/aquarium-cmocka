#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>
#include <errno.h>

#include <test/cmocka/stdlib.h>

_Thread_local bool malloc_is_overridden = false;

void *cmocka_test_malloc(const size_t size, const char *file, const int line) {
    if (malloc_is_overridden) {
        return NULL;
    }
    return _test_malloc(size, file, line);
}

_Thread_local bool calloc_is_overridden = false;

void *cmocka_test_calloc(const size_t nmemb, const size_t size,
                         const char *file, const int line) {
    if (calloc_is_overridden) {
        return NULL;
    }
    return _test_calloc(nmemb, size, file, line);
}

_Thread_local bool realloc_is_overridden = false;

void *cmocka_test_realloc(void *ptr, const size_t size, const char *file,
                          const int line) {
    if (realloc_is_overridden) {
        return NULL;
    }
    return _test_realloc(ptr, size, file, line);
}

void cmocka_test_free(void *ptr, const char *file, const int line) {
    _test_free(ptr, file, line);
}

#undef abort
_Thread_local bool abort_is_overridden = false;

void cmocka_test_abort(const char *file, const int line) {
    if (abort_is_overridden) {
        function_called();
    } else {
        abort();
    }
}

_Thread_local bool posix_memalign_is_overridden = false;

int cmocka_test_posix_memalign(void **const out,
                               const size_t alignment,
                               const size_t size,
                               const char *const file,
                               const int line) {
    assert_non_null(out);
    if (alignment % sizeof(void *)) {
        return EINVAL;
    }
    { /* check for power of 2 */
        size_t i = alignment - 1;
        do { /* expecting bit pattern of consecutive ones */
            if (!(i & 1)) {
                return EINVAL;
            }
            i >>= 1;
        } while (i);
    }
    if (posix_memalign_is_overridden) {
        return ENOMEM;
    }
    void *const ptr = _test_malloc(size, file, line);
    if (!ptr) {
        return ENOMEM;
    }
    *out = ptr;
    return 0;
}

