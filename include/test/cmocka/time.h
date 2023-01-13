#ifndef _CMOCKA_TEST_CMOCKA_TIME_H_
#define _CMOCKA_TEST_CMOCKA_TIME_H_
#ifdef TEST

#include <stddef.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <time.h>

int cmocka_test_clock_gettime(clockid_t clock_id, struct timespec *tp,
                              const char *file, int line);

#define clock_gettime(clock_id, tp) \
    cmocka_test_clock_gettime(clock_id, tp, __FILE__, __LINE__)
extern _Thread_local bool clock_gettime_is_overridden;
extern _Thread_local bool clock_gettime_is_mocked;

#endif /* TEST */
#endif /* _CMOCKA_TEST_CMOCKA_TIME_H_ */
