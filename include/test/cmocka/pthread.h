#ifndef _CMOCKA_TEST_CMOCKA_PTHREAD_H_
#define _CMOCKA_TEST_CMOCKA_PTHREAD_H_
#ifdef TEST

#include <stddef.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <pthread.h>

int cmocka_test_pthread_mutex_init(
        pthread_mutex_t *restrict mutex,
        const pthread_mutexattr_t *restrict attr,
        const char *file, int line);

#define pthread_mutex_init(mutex, attr) \
    cmocka_test_pthread_mutex_init(mutex, attr, __FILE__, __LINE__)
extern _Thread_local bool pthread_mutex_init_is_overridden;

int cmocka_test_pthread_mutex_destroy(pthread_mutex_t *mutex,
                                      const char *file, int line);

#define pthread_mutex_destroy(mutex) \
    cmocka_test_pthread_mutex_destroy(mutex, __FILE__, __LINE__)
extern _Thread_local bool pthread_mutex_destroy_is_overridden;

int cmocka_test_pthread_mutex_lock(pthread_mutex_t *mutex,
                                   const char *file, int line);

#define pthread_mutex_lock(mutex) \
    cmocka_test_pthread_mutex_lock(mutex, __FILE__, __LINE__)
extern _Thread_local bool pthread_mutex_lock_is_overridden;

int cmocka_test_pthread_mutex_trylock(pthread_mutex_t *mutex,
                                      const char *file, int line);

#define pthread_mutex_trylock(mutex) \
    cmocka_test_pthread_mutex_trylock(mutex, __FILE__, __LINE__)
extern _Thread_local bool pthread_mutex_trylock_is_overridden;

int cmocka_test_pthread_mutex_unlock(pthread_mutex_t *mutex,
                                     const char *file, int line);

#define pthread_mutex_unlock(mutex) \
    cmocka_test_pthread_mutex_unlock(mutex, __FILE__, __LINE__)
extern _Thread_local bool pthread_mutex_unlock_is_overridden;

int cmocka_test_pthread_rwlock_init(
        pthread_rwlock_t *restrict rwlock,
        const pthread_rwlockattr_t *restrict attr,
        const char *file, int line);

#define pthread_rwlock_init(rwlock, attr) \
    cmocka_test_pthread_rwlock_init(rwlock, attr, __FILE__, __LINE__)
extern _Thread_local bool pthread_rwlock_init_is_overridden;

int cmocka_test_pthread_rwlock_destroy(pthread_rwlock_t *rwlock,
                                       const char *file, int line);

#define pthread_rwlock_destroy(rwlock) \
    cmocka_test_pthread_rwlock_destroy(rwlock, __FILE__, __LINE__)
extern _Thread_local bool pthread_rwlock_destroy_is_overridden;

int cmocka_test_pthread_rwlock_rdlock(pthread_rwlock_t *rwlock,
                                      const char *file, int line);

#define pthread_rwlock_rdlock(rwlock) \
    cmocka_test_pthread_rwlock_rdlock(rwlock, __FILE__, __LINE__)
extern _Thread_local bool pthread_rwlock_rdlock_is_overridden;

int cmocka_test_pthread_rwlock_tryrdlock(pthread_rwlock_t *rwlock,
                                         const char *file, int line);

#define pthread_rwlock_tryrdlock(rwlock) \
    cmocka_test_pthread_rwlock_tryrdlock(rwlock, __FILE__, __LINE__)
extern _Thread_local bool pthread_rwlock_tryrdlock_is_overridden;

int cmocka_test_pthread_rwlock_wrlock(pthread_rwlock_t *rwlock,
                                      const char *file, int line);

#define pthread_rwlock_wrlock(rwlock) \
    cmocka_test_pthread_rwlock_wrlock(rwlock, __FILE__, __LINE__)
extern _Thread_local bool pthread_rwlock_wrlock_is_overridden;

int cmocka_test_pthread_rwlock_trywrlock(pthread_rwlock_t *rwlock,
                                         const char *file, int line);

#define pthread_rwlock_trywrlock(rwlock) \
    cmocka_test_pthread_rwlock_trywrlock(rwlock, __FILE__, __LINE__)
extern _Thread_local bool pthread_rwlock_trywrlock_is_overridden;

int cmocka_test_pthread_rwlock_unlock(pthread_rwlock_t *rwlock,
                                      const char *file, int line);

#define pthread_rwlock_unlock(rwlock) \
    cmocka_test_pthread_rwlock_unlock(rwlock, __FILE__, __LINE__)
extern _Thread_local bool pthread_rwlock_unlock_is_overridden;

int cmocka_test_pthread_cond_init(pthread_cond_t *restrict cond,
                                  pthread_condattr_t *restrict attr,
                                  const char *file, int line);

#define pthread_cond_init(cond, attr) \
    cmocka_test_pthread_cond_init(cond, attr, __FILE__, __LINE__)
extern _Thread_local bool pthread_cond_init_is_overridden;

int cmocka_test_pthread_cond_destroy(pthread_cond_t *cond,
                                     const char *file, int line);

#define pthread_cond_destroy(cond) \
    cmocka_test_pthread_cond_destroy(cond, __FILE__, __LINE__)
extern _Thread_local bool pthread_cond_destroy_is_overridden;

int cmocka_test_pthread_cond_wait(pthread_cond_t *restrict cond,
                                  pthread_mutex_t *restrict mutex,
                                  const char *file, int line);

#define pthread_cond_wait(cond, mutex) \
    cmocka_test_pthread_cond_wait(cond, mutex, __FILE__, __LINE__)
extern _Thread_local bool pthread_cond_wait_is_overridden;

int cmocka_test_pthread_cond_timedwait(pthread_cond_t *restrict cond,
                                       pthread_mutex_t *restrict mutex,
                                       const struct timespec *restrict abstime,
                                       const char *file, int line);

#define pthread_cond_timedwait(cond, mutex, abstime) \
    cmocka_test_pthread_cond_timedwait(cond, mutex, abstime, __FILE__, __LINE__)
extern _Thread_local bool pthread_cond_timedwait_is_overridden;

int cmocka_test_pthread_cond_broadcast(pthread_cond_t *cond,
                                       const char *file, int line);

#define pthread_cond_broadcast(cond) \
    cmocka_test_pthread_cond_broadcast(cond, __FILE__, __LINE__)
extern _Thread_local bool pthread_cond_broadcast_is_overridden;

int cmocka_test_pthread_cond_signal(pthread_cond_t *cond,
                                    const char *file, int line);

#define pthread_cond_signal(cond) \
    cmocka_test_pthread_cond_signal(cond, __FILE__, __LINE__)
extern _Thread_local bool pthread_cond_signal_is_overridden;

int cmocka_test_pthread_create(pthread_t *restrict thread,
                               const pthread_attr_t *restrict attr,
                               void *(*start_routine)(void *),
                               void *restrict arg,
                               const char *file, int line);

#define pthread_create(thread, attr, start_routine, arg) \
    cmocka_test_pthread_create(thread, attr, start_routine, arg, \
    __FILE__, __LINE__)
extern _Thread_local bool pthread_create_is_overridden;

#endif /* TEST */
#endif /* _CMOCKA_TEST_CMOCKA_PTHREAD_H_ */
