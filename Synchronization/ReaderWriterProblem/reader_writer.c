#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <semaphore.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/wait.h>

#define MAX 3
#define SEM_RW_MUTEX_NAME "/rw_mutex_sem" // Name for the read-write mutex semaphore
#define SEM_MUTEX_NAME "/mutex_sem" // Name for the mutex semaphore

struct shared_data {
    sem_t *rw_mutex; // Semaphore to ensure exclusive access for writer
    sem_t *mutex;    // Semaphore to protect the read_count
    int read_count;
    int var;
};

void writer_process(struct shared_data *shared) {

    while (shared->var < MAX) {
        sem_wait(shared->rw_mutex); // Aquring the lock
        printf("The writer acquired the lock.\n");
        shared->var++;
        printf("The writer (PID %d) writes the value %d\n", getpid(), shared->var);
        sem_post(shared->rw_mutex); // Release the lock
        printf("The writer releases the lock.\n");
        sleep(2);
    }
}

void reader_process(struct shared_data *shared) {
    int hasReadFinalValue = 0;
    
    while (1) {
        // Protect the operation on read_count
        sem_wait(shared->mutex);
        shared->read_count++;

        // If this is the first reader,  wait for the rw_mutex
        // to ensure that no writers can write as long as there's at least one reader reading
        if (shared->read_count == 1) {
            sem_wait(shared->rw_mutex);
            printf("The first reader acquired the lock.\n");
        }
        // Release the mutex to allow other readers to update the read_count
        sem_post(shared->mutex);

        sleep(1);

        printf("Reader (PID %d) reads the final value %d\n", getpid(), shared->var);

        if (shared->var == MAX) {
            hasReadFinalValue = 1;
        }

        sleep(1);

        // Protect the operation on read_count
        sem_wait(shared->mutex);
        shared->read_count--;
        // If this is the last reader, release the rw_mutex to allow writers to write
        if (shared->read_count == 0) {
            sem_post(shared->rw_mutex);
            printf("The last reader releases the lock.\n");
        }
        // Release the mutex to allow other readers to update the read_count
        sem_post(shared->mutex);

        if (hasReadFinalValue) {
            break;
        }
        
        sleep(1);
    }
}


int main() {
    struct shared_data *shared = mmap(NULL, sizeof(struct shared_data), PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
    shared->read_count = 0;
    shared->var = 0;

    shared->rw_mutex = sem_open(SEM_RW_MUTEX_NAME, O_CREAT, 0644, 1);
    shared->mutex = sem_open(SEM_MUTEX_NAME, O_CREAT, 0644, 1);

    pid_t pid1, pid2, pid3;

    // Start the first reader process
    pid1 = fork();
    if (pid1 == 0) {
        reader_process(shared);
        exit(0);
    }

    // Start the second reader process
    pid2 = fork();
    if (pid2 == 0) {
        reader_process(shared);
        exit(0);
    }


    // Start the writer process
    pid3 = fork();
    if (pid3 == 0) {
        writer_process(shared);
        exit(0);
    }

    // Wait for all child processes to finish
    waitpid(pid1, NULL, 0);
    waitpid(pid2, NULL, 0);
    waitpid(pid3, NULL, 0);

    // Cleanup
    sem_close(shared->rw_mutex);
    sem_unlink(SEM_RW_MUTEX_NAME);
    sem_close(shared->mutex);
    sem_unlink(SEM_MUTEX_NAME);
    munmap(shared, sizeof(struct shared_data));

    return 0;
}
