#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>
#include <dlfcn.h>

#include <test/cmocka/pthread.h>

_Thread_local bool pthread_mutex_init_is_overridden = false;

int cmocka_test_pthread_mutex_init(pthread_mutex_t *restrict mutex,
                                   const pthread_mutexattr_t *attr,
                                   const char *file, int line) {
    assert_non_null(mutex);
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
                                    const pthread_rwlockattr_t *attr,
                                    const char *file, int line) {
    assert_non_null(rwlock);
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
