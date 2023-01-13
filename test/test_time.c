#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>
#include <errno.h>

#include <test/cmocka.h>

static void check_clock_gettime(void **state) {
    struct timespec f;
    assert_int_equal(clock_gettime(CLOCK_REALTIME, &f), 0);
    clock_gettime_is_mocked = true;
    struct timespec s;
    will_return(cmocka_test_clock_gettime, &f);
    assert_int_equal(clock_gettime(CLOCK_REALTIME, &s), 0);
    assert_int_equal(f.tv_sec, s.tv_sec);
    assert_int_equal(f.tv_nsec, s.tv_nsec);
    f = (struct timespec) {0};
    will_return(cmocka_test_clock_gettime, &f);
    assert_int_equal(clock_gettime(CLOCK_REALTIME, &s), 0);
    assert_int_equal(f.tv_sec, s.tv_sec);
    assert_int_equal(f.tv_nsec, s.tv_nsec);
    clock_gettime_is_mocked = false;

    const int errors[] = {
            EINVAL, EFAULT, EPERM
    };
    const uintmax_t l = sizeof(errors) / sizeof(int);
    clock_gettime_is_overridden = true;
    for (uintmax_t i = 0; i < l; i++) {
        will_return(cmocka_test_clock_gettime, errors[i]);
        assert_int_equal(clock_gettime(CLOCK_REALTIME, &s), -1);
        assert_int_equal(errno, errors[i]);
    }
    clock_gettime_is_overridden = false;
    assert_int_equal(clock_gettime(CLOCK_REALTIME, &s), 0);
}

int main(int argc, char *argv[]) {
    const struct CMUnitTest tests[] = {
            cmocka_unit_test(check_clock_gettime)
    };
    //cmocka_set_message_output(CM_OUTPUT_XML);
    return cmocka_run_group_tests(tests, NULL, NULL);
}
