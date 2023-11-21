#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define NUM_THREADS 3
#define NUM_ACCESSES 15

int buffer = 0; // Shared buffer accessed by all threads
pthread_mutex_t lock; // Mutex lock for synchronizing access to the buffer

void *thread_function(void *arg) {
    int count = 0; // Track how many times this thread has modified the buffer

    for (int i = 0; i < NUM_ACCESSES; ++i) {
        pthread_mutex_lock(&lock); // Acquire the mutex lock before accessing the buffer
        if (buffer < NUM_ACCESSES) {
            printf("TID: %p, PID: %d, Buffer: %d\n", (void *)pthread_self(), getpid(), buffer);
            buffer++;
            count++;

            pthread_mutex_unlock(&lock); // Release the mutex lock

            // Introduce some variability
            usleep(rand() % 1000000); // Random delay between 0 to 1 s
        } else {
            pthread_mutex_unlock(&lock);
            break;
        }
    }
    return (void *)(size_t)count;
}

int main() {
    pthread_t threads[NUM_THREADS];
    pthread_mutex_init(&lock, NULL); // Initialize the mutex lock

    srand(time(NULL)); // Seed for random number generation

    // Create threads
    for (int i = 0; i < NUM_THREADS; ++i) {
        if (pthread_create(&threads[i], NULL, thread_function, NULL) != 0) {
            perror("Failed to create thread");
            return 1;
        }
    }

    int total_accesses = 0;

    // Wait for all threads to complete and collect their access counts
    for (int i = 0; i < NUM_THREADS; ++i) {
        void *ret;
        pthread_join(threads[i], &ret); // Wait for the ith thread to finish
        int thread_accesses = (int)(size_t)ret;
        printf("TID %p worked on the buffer %d times\n", (void *)threads[i], thread_accesses);
        total_accesses += thread_accesses;
    }

    printf("Total buffer accesses: %d\n", total_accesses);

    pthread_mutex_destroy(&lock);
    return 0;
}
