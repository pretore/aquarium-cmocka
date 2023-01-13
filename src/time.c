#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>
#include <dlfcn.h>
#include <errno.h>

#include <test/cmocka/time.h>

_Thread_local bool clock_gettime_is_overridden = false;
_Thread_local bool clock_gettime_is_mocked = false;

int cmocka_test_clock_gettime(clockid_t clock_id, struct timespec *const tp,
                              const char *const file, int line) {
    if (clock_gettime_is_overridden) {
        errno = mock();
        return (-1);
    }
    if (clock_gettime_is_mocked) {
        *tp = *mock_ptr_type(struct timespec *);
        return 0;
    }
    static int (*func)(clockid_t, const struct timespec *) = NULL;
    if (!func) {
        func = dlsym(RTLD_NEXT, u8"clock_gettime");
        assert_non_null(func);
    }
    return func(clock_id, tp);
}
