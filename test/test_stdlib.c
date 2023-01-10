#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>
#include <string.h>
#include <errno.h>

#include <test/cmocka/stdlib.h>

static void check_malloc(void **state) {
    void *data = malloc(1);
    assert_non_null(data);
    free(data);

    malloc_is_overridden = true;
    data = malloc(1);
    assert_null(data);
    malloc_is_overridden = false;
}

static void check_calloc(void **state) {
    void *data = calloc(1, 1);
    assert_non_null(data);
    free(data);

    calloc_is_overridden = true;
    data = calloc(1, 1);
    assert_null(data);
    calloc_is_overridden = false;
}

static void check_realloc_with_null(void **state) {
    void *data = realloc(NULL, 1);
    assert_non_null(data);
    free(data);

    realloc_is_overridden = true;
    data = realloc(NULL, 1);
    assert_null(data);
    realloc_is_overridden = false;
}

static void check_realloc(void **state) {
    void *data = calloc(1, 1);
    assert_non_null(data);

    realloc_is_overridden = true;
    void *new = realloc(data, 2);
    assert_null(new);
    realloc_is_overridden = false;

    new = realloc(data, 2);
    assert_non_null(new);
    free(new);
}

static void check_abort(void **state) {
    expect_function_call(cmocka_test_abort);
    abort_is_overridden = true;
    abort();
    abort_is_overridden = false;
}

static void check_posix_memalign_error_on_invalid_alignment(void **state) {
    assert_int_equal(posix_memalign((void *)1, 1, sizeof(void *)), EINVAL);
}

static void check_posix_memalign(void **state) {
    void *data = NULL;
    assert_int_equal(posix_memalign(&data, sizeof(void *), sizeof(void *)), 0);
    assert_non_null(data);
    free(data);

    posix_memalign_is_overridden = true;
    assert_int_equal(posix_memalign(&data, sizeof(void *), sizeof(void *)),
                     ENOMEM);
    posix_memalign_is_overridden = false;
}

int main(int argc, char *argv[]) {
    const struct CMUnitTest tests[] = {
            cmocka_unit_test(check_malloc),
            cmocka_unit_test(check_calloc),
            cmocka_unit_test(check_realloc_with_null),
            cmocka_unit_test(check_realloc),
            cmocka_unit_test(check_abort),
            cmocka_unit_test(check_posix_memalign_error_on_invalid_alignment),
            cmocka_unit_test(check_posix_memalign),

    };
    //cmocka_set_message_output(CM_OUTPUT_XML);
    return cmocka_run_group_tests(tests, NULL, NULL);
}

