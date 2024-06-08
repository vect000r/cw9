#ifndef THREADS_H
#define THREADS_H

#include <pthread.h>

pthread_t createThread(void *(*function)(void *), void *arg);
void joinThread(pthread_t thread);
void createMutex(pthread_mutex_t *mutex);
void openMutex(pthread_mutex_t *mutex);
void closeMutex(pthread_mutex_t *mutex);
void deleteMutex(pthread_mutex_t *mutex);

#endif