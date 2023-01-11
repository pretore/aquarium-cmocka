#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>
#include <errno.h>

#include <test/cmocka.h>

static void check_mutex_init(void **state) {
    pthread_mutex_t mutex;
    pthread_mutex_init_is_overridden = true;
    const int error[] = {
            EINVAL, EAGAIN, ENOMEM, EPERM
    };
    const uintmax_t limit = sizeof(error) / sizeof(int);
    for (uintmax_t i = 0; i < limit; i++) {
        will_return(cmocka_test_pthread_mutex_init, error[i]);
        assert_int_equal(pthread_mutex_init(&mutex, NULL), error[i]);
    }
    pthread_mutex_init_is_overridden = false;
    assert_int_equal(pthread_mutex_init(&mutex, NULL), 0);
    assert_int_equal(pthread_mutex_destroy(&mutex), 0);
}

static void check_mutex_destroy(void **state) {
    pthread_mutex_t mutex;
    assert_int_equal(pthread_mutex_init(&mutex, NULL), 0);
    pthread_mutex_destroy_is_overridden = true;
    const int error[] = {
            EINVAL, EBUSY
    };
    const uintmax_t limit = sizeof(error) / sizeof(int);
    for (uintmax_t i = 0; i < limit; i++) {
        will_return(cmocka_test_pthread_mutex_destroy, error[i]);
        assert_int_equal(pthread_mutex_destroy(&mutex), error[i]);
    }
    pthread_mutex_destroy_is_overridden = false;
    assert_int_equal(pthread_mutex_destroy(&mutex), 0);
}

static void check_mutex_lock(void **state) {
    pthread_mutex_t mutex;
    assert_int_equal(pthread_mutex_init(&mutex, NULL), 0);
    pthread_mutex_lock_is_overridden = true;
    const int error[] = {
            EINVAL, EAGAIN, EDEADLK
    };
    const uintmax_t limit = sizeof(error) / sizeof(int);
    for (uintmax_t i = 0; i < limit; i++) {
        will_return(cmocka_test_pthread_mutex_lock, error[i]);
        assert_int_equal(pthread_mutex_lock(&mutex), error[i]);
    }
    pthread_mutex_lock_is_overridden = false;
    assert_int_equal(pthread_mutex_lock(&mutex), 0);
    assert_int_equal(pthread_mutex_unlock(&mutex), 0);
    assert_int_equal(pthread_mutex_destroy(&mutex), 0);
}

static void check_mutex_trylock(void **state) {
    pthread_mutex_t mutex;
    assert_int_equal(pthread_mutex_init(&mutex, NULL), 0);
    pthread_mutex_lock_is_overridden = true;
    const int error[] = {
            EINVAL, EBUSY, EAGAIN
    };
    const uintmax_t limit = sizeof(error) / sizeof(int);
    for (uintmax_t i = 0; i < limit; i++) {
        will_return(cmocka_test_pthread_mutex_lock, error[i]);
        assert_int_equal(pthread_mutex_lock(&mutex), error[i]);
    }
    pthread_mutex_lock_is_overridden = false;
    assert_int_equal(pthread_mutex_trylock(&mutex), 0);
    assert_int_equal(pthread_mutex_trylock(&mutex), EBUSY);
    assert_int_equal(pthread_mutex_unlock(&mutex), 0);
    assert_int_equal(pthread_mutex_destroy(&mutex), 0);
}

static void check_mutex_unlock(void **state) {
    pthread_mutex_t mutex;
    assert_int_equal(pthread_mutex_init(&mutex, NULL), 0);
    assert_int_equal(pthread_mutex_lock(&mutex), 0);
    pthread_mutex_unlock_is_overridden = true;
    const int error[] = {
            EINVAL, EAGAIN, EPERM
    };
    const uintmax_t limit = sizeof(error) / sizeof(int);
    for (uintmax_t i = 0; i < limit; i++) {
        will_return(cmocka_test_pthread_mutex_unlock, error[i]);
        assert_int_equal(pthread_mutex_unlock(&mutex), error[i]);
    }
    pthread_mutex_unlock_is_overridden = false;
    assert_int_equal(pthread_mutex_unlock(&mutex), 0);
    assert_int_equal(pthread_mutex_destroy(&mutex), 0);
}

static void check_rwlock_init(void **state) {
    pthread_rwlock_t rwlock;
    pthread_rwlock_init_is_overridden = true;
    const int error[] = {
            EAGAIN, ENOMEM, EPERM, EBUSY, EINVAL
    };
    const uintmax_t limit = sizeof(error) / sizeof(int);
    for (uintmax_t i = 0; i < limit; i++) {
        will_return(cmocka_test_pthread_rwlock_init, error[i]);
        assert_int_equal(pthread_rwlock_init(&rwlock, NULL), error[i]);
    }
    pthread_rwlock_init_is_overridden = false;
    assert_int_equal(pthread_rwlock_init(&rwlock, NULL), 0);
    assert_int_equal(pthread_rwlock_destroy(&rwlock), 0);
}

static void check_rwlock_destroy(void **state) {
    pthread_rwlock_t rwlock;
    assert_int_equal(pthread_rwlock_init(&rwlock, NULL), 0);
    pthread_rwlock_destroy_is_overridden = true;
    const int error[] = {
            EBUSY, EINVAL
    };
    const uintmax_t limit = sizeof(error) / sizeof(int);
    for (uintmax_t i = 0; i < limit; i++) {
        will_return(cmocka_test_pthread_rwlock_destroy, error[i]);
        assert_int_equal(pthread_rwlock_destroy(&rwlock), error[i]);
    }
    pthread_rwlock_destroy_is_overridden = false;
    assert_int_equal(pthread_rwlock_destroy(&rwlock), 0);
}

static void check_rwlock_rdlock(void **state) {
    pthread_rwlock_t rwlock;
    assert_int_equal(pthread_rwlock_init(&rwlock, NULL), 0);
    pthread_rwlock_rdlock_is_overridden = true;
    const int error[] = {
            EINVAL, EAGAIN, EDEADLK
    };
    const uintmax_t limit = sizeof(error) / sizeof(int);
    for (uintmax_t i = 0; i < limit; i++) {
        will_return(cmocka_test_pthread_rwlock_rdlock, error[i]);
        assert_int_equal(pthread_rwlock_rdlock(&rwlock), error[i]);
    }
    pthread_rwlock_rdlock_is_overridden = false;
    assert_int_equal(pthread_rwlock_rdlock(&rwlock), 0);
    assert_int_equal(pthread_rwlock_unlock(&rwlock), 0);
    assert_int_equal(pthread_rwlock_destroy(&rwlock), 0);
}

static void check_rwlock_tryrdlock(void **state) {
    pthread_rwlock_t rwlock;
    assert_int_equal(pthread_rwlock_init(&rwlock, NULL), 0);
    pthread_rwlock_tryrdlock_is_overridden = true;
    const int error[] = {
            EBUSY, EINVAL, EAGAIN
    };
    const uintmax_t limit = sizeof(error) / sizeof(int);
    for (uintmax_t i = 0; i < limit; i++) {
        will_return(cmocka_test_pthread_rwlock_tryrdlock, error[i]);
        assert_int_equal(pthread_rwlock_tryrdlock(&rwlock), error[i]);
    }
    pthread_rwlock_tryrdlock_is_overridden = false;
    assert_int_equal(pthread_rwlock_tryrdlock(&rwlock), 0);
    assert_int_equal(pthread_rwlock_tryrdlock(&rwlock), 0);
    assert_int_equal(pthread_rwlock_unlock(&rwlock), 0);
    assert_int_equal(pthread_rwlock_unlock(&rwlock), 0);
    assert_int_equal(pthread_rwlock_destroy(&rwlock), 0);
}

static void check_rwlock_wrlock(void **state) {
    pthread_rwlock_t rwlock;
    assert_int_equal(pthread_rwlock_init(&rwlock, NULL), 0);
    pthread_rwlock_wrlock_is_overridden = true;
    const int error[] = {
            EINVAL, EDEADLK
    };
    const uintmax_t limit = sizeof(error) / sizeof(int);
    for (uintmax_t i = 0; i < limit; i++) {
        will_return(cmocka_test_pthread_rwlock_wrlock, error[i]);
        assert_int_equal(pthread_rwlock_wrlock(&rwlock), error[i]);
    }
    pthread_rwlock_wrlock_is_overridden = false;
    assert_int_equal(pthread_rwlock_wrlock(&rwlock), 0);
    assert_int_equal(pthread_rwlock_unlock(&rwlock), 0);
    assert_int_equal(pthread_rwlock_destroy(&rwlock), 0);
}

static void check_rwlock_trywrlock(void **state) {
    pthread_rwlock_t rwlock;
    assert_int_equal(pthread_rwlock_init(&rwlock, NULL), 0);
    pthread_rwlock_trywrlock_is_overridden = true;
    const int error[] = {
            EBUSY, EINVAL
    };
    const uintmax_t limit = sizeof(error) / sizeof(int);
    for (uintmax_t i = 0; i < limit; i++) {
        will_return(cmocka_test_pthread_rwlock_trywrlock, error[i]);
        assert_int_equal(pthread_rwlock_trywrlock(&rwlock), error[i]);
    }
    pthread_rwlock_trywrlock_is_overridden = false;
    assert_int_equal(pthread_rwlock_trywrlock(&rwlock), 0);
    assert_int_equal(pthread_rwlock_unlock(&rwlock), 0);
    assert_int_equal(pthread_rwlock_destroy(&rwlock), 0);
}

static void check_rwlock_unlock(void **state) {
    pthread_rwlock_t rwlock;
    assert_int_equal(pthread_rwlock_init(&rwlock, NULL), 0);
    assert_int_equal(pthread_rwlock_rdlock(&rwlock), 0);
    pthread_rwlock_unlock_is_overridden = true;
    const int error[] = {
            EINVAL, EPERM
    };
    const uintmax_t limit = sizeof(error) / sizeof(int);
    for (uintmax_t i = 0; i < limit; i++) {
        will_return(cmocka_test_pthread_rwlock_unlock, error[i]);
        assert_int_equal(pthread_rwlock_unlock(&rwlock), error[i]);
    }
    pthread_rwlock_unlock_is_overridden = false;
    assert_int_equal(pthread_rwlock_unlock(&rwlock), 0);
    assert_int_equal(pthread_rwlock_destroy(&rwlock), 0);
}

int main(int argc, char *argv[]) {
    const struct CMUnitTest tests[] = {
            cmocka_unit_test(check_mutex_init),
            cmocka_unit_test(check_mutex_destroy),
            cmocka_unit_test(check_mutex_lock),
            cmocka_unit_test(check_mutex_trylock),
            cmocka_unit_test(check_mutex_unlock),
            cmocka_unit_test(check_rwlock_init),
            cmocka_unit_test(check_rwlock_destroy),
            cmocka_unit_test(check_rwlock_rdlock),
            cmocka_unit_test(check_rwlock_tryrdlock),
            cmocka_unit_test(check_rwlock_wrlock),
            cmocka_unit_test(check_rwlock_trywrlock),
            cmocka_unit_test(check_rwlock_unlock),
    };
    //cmocka_set_message_output(CM_OUTPUT_XML);
    return cmocka_run_group_tests(tests, NULL, NULL);
}
