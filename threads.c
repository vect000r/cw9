#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <pthread.h>
#include <string.h>
// Funkcja tworząca wątek

pthread_t createThread(void *(*function)(void *), void *arg) {
    pthread_t thread;
    int rc = pthread_create(&thread, NULL, function, arg);
    if (rc) {
        printf("Failed to create a thread with error code: %s\n", strerror(errno));
        exit(1);
    }
    return thread;
}

// Funkcja łącząca wątek

void joinThread(pthread_t thread) {
    int rc = pthread_join(thread, NULL);
    if (rc) {
        printf("Failed to join a thread with error code: %s\n", strerror(errno));
        exit(1);
    }
}

// Funkcja inicjalizująca mutex

void createMutex(pthread_mutex_t *mutex) {
    int rc = pthread_mutex_init(mutex, NULL);
    if (rc) {
        printf("Failed to create a mutex with error code: %s\n", strerror(errno));
        exit(1);
    }
}

// Funkcja otwierająca mutex

void openMutex(pthread_mutex_t *mutex) {
    int rc = pthread_mutex_unlock(mutex);
    if (rc) {
        printf("Failed to unlock a mutex with error code: %s\n", strerror(errno));
        exit(1);
    }
}

// Funkcja zamykająca mutex

void closeMutex(pthread_mutex_t *mutex) {
    int rc = pthread_mutex_lock(mutex);
    if (rc) {
        printf("Failed to lock a mutex with error code: %s\n", strerror(errno));
        exit(1);
    }
}

// Funkcja usuwająca mutex

void deleteMutex(pthread_mutex_t *mutex) {
    int rc = pthread_mutex_destroy(mutex);
    if (rc) {
        printf("Failed to destroy a mutex with error code: %s\n", strerror(errno));
        exit(1);
    }
}