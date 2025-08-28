/*
===============================================================================
Program: Producer-Consumer Synchronization using pthreads, mutex, and condition
-------------------------------------------------------------------------------
Description:
This program demonstrates the use of pthreads with mutex and condition 
variables in C. It simulates a simple producer-consumer scenario:

- Thread 1 (fun1) acts as a consumer. It waits until the data is ready. 
  Once signaled, it prints the contents of the array.
- Thread 2 (fun2) acts as a producer. It takes input from the user, fills 
  the array, sets the 'ready' flag, and signals the consumer.

Key Concepts:
- pthread_mutex_t ensures mutual exclusion (only one thread can access the 
  shared resource at a time).
- pthread_cond_t allows one thread to wait until another signals it.
- pthread_cond_wait() atomically releases the mutex and puts the thread to 
  sleep until it receives a signal from pthread_cond_broadcast() or 
  pthread_cond_signal().
===============================================================================
*/

#include <stdio.h>
#include <pthread.h>
#define BUFFER_SIZE 5   // Size of the shared buffer

pthread_cond_t cond;       // Condition variable for signaling
pthread_mutex_t mutex;     // Mutex for synchronization

int array[BUFFER_SIZE];    // Shared buffer
int ready = 0;             // Flag to indicate if data is ready

// Consumer thread: waits for producer and prints the data
void *fun1(void *arg)  {
    pthread_mutex_lock(&mutex);   // Acquire the mutex

    // Wait until data is ready
    while (ready == 0) {
        pthread_cond_wait(&cond, &mutex);
        // Automatically releases mutex while waiting
        // Reacquires mutex before returning
    }

    // Print the data from the shared buffer
    for (int i = 0; i < BUFFER_SIZE; i++) {
        printf("Data[%d] : %d\n", i, array[i]);
    }

    pthread_mutex_unlock(&mutex);  // Release the mutex
    return NULL;
}

// Producer thread: reads input and signals consumer
void *fun2(void *arg) {
    pthread_mutex_lock(&mutex);   // Acquire the mutex
    
    // Take input from the user
    for (int i = 0; i < BUFFER_SIZE; i++) {
        printf("Enter the data : ");
        scanf("%d", &array[i]);
    }

    // Mark data as ready
    ready = 1;

    // Signal all waiting threads that data is ready
    pthread_cond_broadcast(&cond);

    pthread_mutex_unlock(&mutex);  // Release the mutex
    return NULL;
}

int main() {
    pthread_t thread1, thread2;

    // Initialize mutex and condition variable
    pthread_mutex_init(&mutex, NULL);
    pthread_cond_init(&cond, NULL);

    // Create consumer and producer threads
    pthread_create(&thread1, NULL, fun1, NULL);
    pthread_create(&thread2, NULL, fun2, NULL);

    // Wait for both threads to finish
    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    // Destroy mutex and condition variable
    pthread_mutex_destroy(&mutex);
    pthread_cond_destroy(&cond);

    return 0;
}

