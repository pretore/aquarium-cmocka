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

static void check_cond_init(void **state) {
    pthread_cond_t cond;
    pthread_cond_init_is_overridden = true;
    const int error[] = {
            EAGAIN, ENOMEM, EBUSY, EINVAL
    };
    const uintmax_t limit = sizeof(error) / sizeof(int);
    for (uintmax_t i = 0; i < limit; i++) {
        will_return(cmocka_test_pthread_cond_init, error[i]);
        assert_int_equal(pthread_cond_init(&cond, NULL), error[i]);
    }
    pthread_cond_init_is_overridden = false;
    assert_int_equal(pthread_cond_init(&cond, NULL), 0);
    assert_int_equal(pthread_cond_destroy(&cond), 0);
}

static void check_cond_destroy(void **state) {
    pthread_cond_t cond;
    assert_int_equal(pthread_cond_init(&cond, NULL), 0);
    pthread_cond_destroy_is_overridden = true;
    const int error[] = {
            EBUSY, EINVAL
    };
    const uintmax_t limit = sizeof(error) / sizeof(int);
    for (uintmax_t i = 0; i < limit; i++) {
        will_return(cmocka_test_pthread_cond_destroy, error[i]);
        assert_int_equal(pthread_cond_destroy(&cond), error[i]);
    }
    pthread_cond_destroy_is_overridden = false;
    assert_int_equal(pthread_cond_destroy(&cond), 0);
}

static bool signal_cond_wait;

static void *signal_cond_routine(void *a) {
    pthread_detach(pthread_self());
    assert_non_null(a);
    signal_cond_wait = true;
    pthread_cond_signal(a);
    return NULL;
}

static void check_cond_wait(void **state) {
    pthread_cond_t cond;
    assert_int_equal(pthread_cond_init(&cond, NULL), 0);
    pthread_mutex_t mutex;
    assert_int_equal(pthread_mutex_init(&mutex, NULL), 0);
    pthread_cond_wait_is_overridden = true;
    const int error[] = {
            EINVAL, EPERM
    };
    const uintmax_t limit = sizeof(error) / sizeof(int);
    for (uintmax_t i = 0; i < limit; i++) {
        will_return(cmocka_test_pthread_cond_wait, error[i]);
        assert_int_equal(pthread_cond_wait(&cond, &mutex), error[i]);
    }
    pthread_cond_wait_is_overridden = false;

    /* shared variable for loop */
    signal_cond_wait = false;
    /* acquire mutex */
    assert_int_equal(pthread_mutex_lock(&mutex), 0);
    pthread_t thread;
    assert_int_equal(pthread_create(&thread, NULL, signal_cond_routine,
                                    &cond), 0);
    /* loop on condition */
    while (!signal_cond_wait) {
        /* wait for signal */
        assert_int_equal(pthread_cond_wait(&cond, &mutex), 0);
    }
    /* release mutex */
    assert_int_equal(pthread_mutex_unlock(&mutex), 0);

    assert_int_equal(pthread_mutex_destroy(&mutex), 0);
    assert_int_equal(pthread_cond_destroy(&cond), 0);
}

static void check_cond_timedwait(void **state) {
    pthread_cond_t cond;
    assert_int_equal(pthread_cond_init(&cond, NULL), 0);
    pthread_mutex_t mutex;
    assert_int_equal(pthread_mutex_init(&mutex, NULL), 0);
    pthread_cond_timedwait_is_overridden = true;
    const int error[] = {
            EINVAL, EPERM, ETIMEDOUT
    };
    const uintmax_t limit = sizeof(error) / sizeof(int);
    struct timespec at;
    for (uintmax_t i = 0; i < limit; i++) {
        assert_int_equal(clock_gettime(CLOCK_REALTIME, &at), 0);
        at.tv_sec += 60;
        will_return(cmocka_test_pthread_cond_timedwait, error[i]);
        assert_int_equal(pthread_cond_timedwait(&cond, &mutex, &at), error[i]);
    }
    pthread_cond_timedwait_is_overridden = false;

    /* shared variable for loop */
    signal_cond_wait = false;
    /* acquire mutex */
    assert_int_equal(pthread_mutex_lock(&mutex), 0);
    pthread_t thread;
    assert_int_equal(pthread_create(&thread, NULL, signal_cond_routine,
                                    &cond), 0);
    assert_int_equal(clock_gettime(CLOCK_REALTIME, &at), 0);
    at.tv_sec += 60;
    /* loop on condition */
    while (!signal_cond_wait) {
        /* wait for signal */
        assert_int_equal(pthread_cond_timedwait(&cond, &mutex, &at), 0);
    }
    /* release mutex */
    assert_int_equal(pthread_mutex_unlock(&mutex), 0);

    assert_int_equal(pthread_mutex_destroy(&mutex), 0);
    assert_int_equal(pthread_cond_destroy(&cond), 0);
}

static void check_cond_broadcast(void **state) {
    pthread_cond_t cond;
    assert_int_equal(pthread_cond_init(&cond, NULL), 0);
    pthread_cond_broadcast_is_overridden = true;
    const int error[] = {
            EINVAL
    };
    const uintmax_t limit = sizeof(error) / sizeof(int);
    for (uintmax_t i = 0; i < limit; i++) {
        will_return(cmocka_test_pthread_cond_broadcast, error[i]);
        assert_int_equal(pthread_cond_broadcast(&cond), error[i]);
    }
    pthread_cond_broadcast_is_overridden = false;
    assert_int_equal(pthread_cond_broadcast(&cond), 0);
    assert_int_equal(pthread_cond_destroy(&cond), 0);
}

static void check_cond_signal(void **state) {
    pthread_cond_t cond;
    assert_int_equal(pthread_cond_init(&cond, NULL), 0);
    pthread_cond_signal_is_overridden = true;
    const int error[] = {
            EINVAL
    };
    const uintmax_t limit = sizeof(error) / sizeof(int);
    for (uintmax_t i = 0; i < limit; i++) {
        will_return(cmocka_test_pthread_cond_signal, error[i]);
        assert_int_equal(pthread_cond_signal(&cond), error[i]);
    }
    pthread_cond_signal_is_overridden = false;
    assert_int_equal(pthread_cond_signal(&cond), 0);
    assert_int_equal(pthread_cond_destroy(&cond), 0);
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
            cmocka_unit_test(check_cond_init),
            cmocka_unit_test(check_cond_destroy),
            cmocka_unit_test(check_cond_wait),
            cmocka_unit_test(check_cond_timedwait),
            cmocka_unit_test(check_cond_broadcast),
            cmocka_unit_test(check_cond_signal),
    };
    //cmocka_set_message_output(CM_OUTPUT_XML);
    return cmocka_run_group_tests(tests, NULL, NULL);
}
