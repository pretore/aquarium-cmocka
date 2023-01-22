#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>
#include <dlfcn.h>

#include <test/cmocka/pthread.h>

_Thread_local bool pthread_mutex_init_is_overridden = false;

int cmocka_test_pthread_mutex_init(pthread_mutex_t *restrict mutex,
                                   const pthread_mutexattr_t *restrict attr,
                                   const char *file, int line) {
    assert_non_null(mutex);
    assert_ptr_not_equal(mutex, attr);
    if (pthread_mutex_init_is_overridden) {
        return mock();
    }
    static int (*func)(pthread_mutex_t *, const pthread_mutexattr_t *) = NULL;
    if (!func) {
        func = dlsym(RTLD_NEXT, u8"pthread_mutex_init");
        assert_non_null(func);
    }
    return func(mutex, attr);
}

_Thread_local bool pthread_mutex_destroy_is_overridden = false;

int cmocka_test_pthread_mutex_destroy(pthread_mutex_t *mutex,
                                      const char *file, int line) {
    assert_non_null(mutex);
    if (pthread_mutex_destroy_is_overridden) {
        return mock();
    }
    static int (*func)(pthread_mutex_t *) = NULL;
    if (!func) {
        func = dlsym(RTLD_NEXT, u8"pthread_mutex_destroy");
        assert_non_null(func);
    }
    return func(mutex);
}

_Thread_local bool pthread_mutex_lock_is_overridden = false;

int cmocka_test_pthread_mutex_lock(pthread_mutex_t *mutex,
                                   const char *file, int line) {
    assert_non_null(mutex);
    if (pthread_mutex_lock_is_overridden) {
        return mock();
    }
    static int (*func)(pthread_mutex_t *) = NULL;
    if (!func) {
        func = dlsym(RTLD_NEXT, u8"pthread_mutex_lock");
        assert_non_null(func);
    }
    return func(mutex);
}

_Thread_local bool pthread_mutex_trylock_is_overridden = false;

int cmocka_test_pthread_mutex_trylock(pthread_mutex_t *mutex,
                                      const char *file, int line) {
    assert_non_null(mutex);
    if (pthread_mutex_trylock_is_overridden) {
        return mock();
    }
    static int (*func)(pthread_mutex_t *) = NULL;
    if (!func) {
        func = dlsym(RTLD_NEXT, u8"pthread_mutex_trylock");
        assert_non_null(func);
    }
    return func(mutex);
}

_Thread_local bool pthread_mutex_unlock_is_overridden = false;

int cmocka_test_pthread_mutex_unlock(pthread_mutex_t *mutex,
                                     const char *file, int line) {
    assert_non_null(mutex);
    if (pthread_mutex_unlock_is_overridden) {
        return mock();
    }
    static int (*func)(pthread_mutex_t *) = NULL;
    if (!func) {
        func = dlsym(RTLD_NEXT, u8"pthread_mutex_unlock");
        assert_non_null(func);
    }
    return func(mutex);
}

_Thread_local bool pthread_rwlock_init_is_overridden = false;

int cmocka_test_pthread_rwlock_init(pthread_rwlock_t *restrict rwlock,
                                    const pthread_rwlockattr_t *restrict attr,
                                    const char *file, int line) {
    assert_non_null(rwlock);
    assert_ptr_not_equal(rwlock, attr);
    if (pthread_rwlock_init_is_overridden) {
        return mock();
    }
    static int (*func)(pthread_rwlock_t *, const pthread_rwlockattr_t *) = NULL;
    if (!func) {
        func = dlsym(RTLD_NEXT, u8"pthread_rwlock_init");
        assert_non_null(func);
    }
    return func(rwlock, attr);
}

_Thread_local bool pthread_rwlock_destroy_is_overridden = false;

int cmocka_test_pthread_rwlock_destroy(pthread_rwlock_t *rwlock,
                                       const char *file, int line) {
    assert_non_null(rwlock);
    if (pthread_rwlock_destroy_is_overridden) {
        return mock();
    }
    static int (*func)(pthread_rwlock_t *) = NULL;
    if (!func) {
        func = dlsym(RTLD_NEXT, u8"pthread_rwlock_destroy");
        assert_non_null(func);
    }
    return func(rwlock);
}

_Thread_local bool pthread_rwlock_rdlock_is_overridden = false;

int cmocka_test_pthread_rwlock_rdlock(pthread_rwlock_t *rwlock,
                                      const char *file, int line) {
    assert_non_null(rwlock);
    if (pthread_rwlock_rdlock_is_overridden) {
        return mock();
    }
    static int (*func)(pthread_rwlock_t *) = NULL;
    if (!func) {
        func = dlsym(RTLD_NEXT, u8"pthread_rwlock_rdlock");
        assert_non_null(func);
    }
    return func(rwlock);
}

_Thread_local bool pthread_rwlock_tryrdlock_is_overridden = false;

int cmocka_test_pthread_rwlock_tryrdlock(pthread_rwlock_t *rwlock,
                                         const char *file, int line) {
    assert_non_null(rwlock);
    if (pthread_rwlock_tryrdlock_is_overridden) {
        return mock();
    }
    static int (*func)(pthread_rwlock_t *) = NULL;
    if (!func) {
        func = dlsym(RTLD_NEXT, u8"pthread_rwlock_tryrdlock");
        assert_non_null(func);
    }
    return func(rwlock);
}

_Thread_local bool pthread_rwlock_wrlock_is_overridden = false;

int cmocka_test_pthread_rwlock_wrlock(pthread_rwlock_t *rwlock,
                                      const char *file, int line) {
    assert_non_null(rwlock);
    if (pthread_rwlock_wrlock_is_overridden) {
        return mock();
    }
    static int (*func)(pthread_rwlock_t *) = NULL;
    if (!func) {
        func = dlsym(RTLD_NEXT, u8"pthread_rwlock_wrlock");
        assert_non_null(func);
    }
    return func(rwlock);
}

_Thread_local bool pthread_rwlock_trywrlock_is_overridden = false;

int cmocka_test_pthread_rwlock_trywrlock(pthread_rwlock_t *rwlock,
                                         const char *file, int line) {
    assert_non_null(rwlock);
    if (pthread_rwlock_trywrlock_is_overridden) {
        return mock();
    }
    static int (*func)(pthread_rwlock_t *) = NULL;
    if (!func) {
        func = dlsym(RTLD_NEXT, u8"pthread_rwlock_trywrlock");
        assert_non_null(func);
    }
    return func(rwlock);
}

_Thread_local bool pthread_rwlock_unlock_is_overridden = false;

int cmocka_test_pthread_rwlock_unlock(pthread_rwlock_t *rwlock,
                                      const char *file, int line) {
    assert_non_null(rwlock);
    if (pthread_rwlock_unlock_is_overridden) {
        return mock();
    }
    static int (*func)(pthread_rwlock_t *) = NULL;
    if (!func) {
        func = dlsym(RTLD_NEXT, u8"pthread_rwlock_unlock");
        assert_non_null(func);
    }
    return func(rwlock);
}

_Thread_local bool pthread_cond_init_is_overridden = false;

int cmocka_test_pthread_cond_init(pthread_cond_t *restrict cond,
                                  pthread_condattr_t *restrict attr,
                                  const char *file, int line) {
    assert_non_null(cond);
    assert_ptr_not_equal(cond, attr);
    if (pthread_cond_init_is_overridden) {
        return mock();
    }
    static int (*func)(pthread_cond_t *, pthread_condattr_t *) = NULL;
    if (!func) {
        func = dlsym(RTLD_NEXT, u8"pthread_cond_init");
        assert_non_null(func);
    }
    return func(cond, attr);
}

_Thread_local bool pthread_cond_destroy_is_overridden = false;

int cmocka_test_pthread_cond_destroy(pthread_cond_t *cond,
                                     const char *file, int line) {
    assert_non_null(cond);
    if (pthread_cond_destroy_is_overridden) {
        return mock();
    }
    static int (*func)(pthread_cond_t *) = NULL;
    if (!func) {
        func = dlsym(RTLD_NEXT, u8"pthread_cond_destroy");
        assert_non_null(func);
    }
    return func(cond);
}

_Thread_local bool pthread_cond_wait_is_overridden = false;

int cmocka_test_pthread_cond_wait(pthread_cond_t *restrict cond,
                                  pthread_mutex_t *restrict mutex,
                                  const char *file, int line) {
    assert_non_null(cond);
    assert_non_null(mutex);
    assert_ptr_not_equal(cond, mutex);
    if (pthread_cond_wait_is_overridden) {
        return mock();
    }
    static int (*func)(pthread_cond_t *, pthread_mutex_t *) = NULL;
    if (!func) {
        func = dlsym(RTLD_NEXT, u8"pthread_cond_wait");
        assert_non_null(func);
    }
    return func(cond, mutex);
}

_Thread_local bool pthread_cond_timedwait_is_overridden = false;

int cmocka_test_pthread_cond_timedwait(pthread_cond_t *restrict cond,
                                       pthread_mutex_t *restrict mutex,
                                       const struct timespec *restrict abstime,
                                       const char *file, int line) {
    assert_non_null(cond);
    assert_non_null(mutex);
    assert_non_null(abstime);
    assert_ptr_not_equal(cond, mutex);
    assert_ptr_not_equal(mutex, abstime);
    assert_ptr_not_equal(abstime, cond);
    if (pthread_cond_timedwait_is_overridden) {
        return mock();
    }
    static int (*func)(pthread_cond_t *, pthread_mutex_t *,
                       const struct timespec *);
    if (!func) {
        func = dlsym(RTLD_NEXT, u8"pthread_cond_timedwait");
        assert_non_null(func);
    }
    return func(cond, mutex, abstime);
}

_Thread_local bool pthread_cond_broadcast_is_overridden = false;

int cmocka_test_pthread_cond_broadcast(pthread_cond_t *cond,
                                       const char *file, int line) {
    assert_non_null(cond);
    if (pthread_cond_broadcast_is_overridden) {
        return mock();
    }
    static int (*func)(pthread_cond_t *) = NULL;
    if (!func) {
        func = dlsym(RTLD_NEXT, u8"pthread_cond_broadcast");
        assert_non_null(func);
    }
    return func(cond);
}

_Thread_local bool pthread_cond_signal_is_overridden = false;

int cmocka_test_pthread_cond_signal(pthread_cond_t *cond,
                                    const char *file, int line) {
    assert_non_null(cond);
    if (pthread_cond_signal_is_overridden) {
        return mock();
    }
    static int (*func)(pthread_cond_t *) = NULL;
    if (!func) {
        func = dlsym(RTLD_NEXT, u8"pthread_cond_signal");
        assert_non_null(func);
    }
    return func(cond);
}

_Thread_local bool pthread_create_is_overridden = false;

int cmocka_test_pthread_create(pthread_t *restrict thread,
                               const pthread_attr_t *restrict attr,
                               void *(*start_routine)(void *),
                               void *restrict arg,
                               const char *file, int line) {
    assert_non_null(thread);
    assert_non_null(start_routine);
    assert_ptr_not_equal(thread, attr);
    assert_ptr_not_equal(thread, arg);
    if (pthread_create_is_overridden) {
        return mock();
    }
    static int (*func)(pthread_t *,
                       const pthread_attr_t *,
                       void *(*)(void *),
                       void *) = NULL;
    if (!func) {
        func = dlsym(RTLD_NEXT, u8"pthread_create");
        assert_non_null(func);
    }
    return func(thread, attr, start_routine, arg);
}
