#define _REENTRANT

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <pthread.h>
#include "threads.h"

#define MAX_THREADS 10

pthread_mutex_t mutex;
int number;
unsigned int threads_count; 
unsigned int section_count;

void *thread_start(void *arg)
{
    srand(time(NULL));
    
    int counter = 0;
    int thread_number = *(int*)arg;

    printf("Thread number: %d, thread id: %lu\n", thread_number, pthread_self());
    sleep(1);

    for(int i = 0; i < section_count; i++)
    {
        // s prywatna
        printf("Thread number: %d, private section number: %d, number: %d\n", thread_number + 1, i + 1, number);

        sleep(rand() % 5 + 1);

        //////////////////////////
        // s krytyczna
        closeMutex(&mutex);
        printf("                            Thread number: %d, critical section number: %d, number: %d\n", thread_number + 1, i + 1, number);
        
        counter = number;
        counter++;

        sleep(rand() % 5 + 1);

        number = counter;

        //////////////////////////
    
        openMutex(&mutex);

        printf("Thread number: %d, private section number: %d, number: %d\n", thread_number + 1, i + 1, number);

        sleep(rand() % 5 + 1);    
    }

    return 0;
}

int main(int argc, char *argv[])
{
    if(argc != 3)
    {
        printf("Wrong number of arguments\n");
        exit(EXIT_FAILURE);
    }

    threads_count = atoi(argv[1]);
    section_count = atoi(argv[2]);

    if(threads_count > MAX_THREADS)
    {
        printf("Too many threads\n");
        exit(EXIT_FAILURE);
    }

    pthread_t threads[threads_count];
    int thread_numbers[threads_count];

    number = 0;

    createMutex(&mutex);

    // tworzymy wątki

    for(int i = 0; i < threads_count; i++)
    {
        int *buffer = malloc(sizeof(int));
        *buffer = i;
        threads[i] = createThread(thread_start, (void *)buffer);
    }

    for(int i = 0; i < threads_count; i++)
    {
        joinThread(threads[i]);
    }

    // numer jest poprawny jeśli jest równy liczbie wątków * liczba sekcji
    
    if(number == threads_count * section_count)
    {
        printf("Number is correct\n");
    }
    else
    {
        printf("Number is incorrect\n");
    }
    deleteMutex(&mutex);
    return 0;
}