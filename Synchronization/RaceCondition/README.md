## Mutexes in Process Synchronization

Synchronization is crucial in concurrent programming to ensure that multiple processes or threads can operate in a safe and predictable manner, particularly when interacting with shared resources.

A mutex (mutual exclusion) is a synchronization mechanism used to control access to a shared resource in a multi-threaded environment. It allows only one thread to access a critical section at a time, preventing concurrent access which could lead to race conditions. Mutexes are essential tools in an operating system's toolkit to manage concurrent processes or threads, ensuring data integrity and consistency by preventing race conditions.

This lab involves the task of coding `MutexThreadBufferIncrement.c`, a program that exemplifies the practical implementation of mutexes in C by using the POSIX threads (pthreads) library. The program illustrates how threads can safely and sequentially access and modify a shared resource, in this case, a shared integer buffer.

### Details
- The program creates three threads, each of which accesses a shared integer called `buffer`.
- Initially, `buffer` is set to 0. Each thread prints its thread ID, process ID, and the current value of `buffer`, then increments `buffer` by one.
- A mutex lock is employed to ensure that the threads access and modify the buffer one at a time, demonstrating the concept of mutual exclusion.
- Each thread modifies the buffer 15 times in total. The final output shows the number of times each thread changed the buffer, along with the total buffer accesses.


## Usage
To compile and run the program:

```bash
gcc -o MutexThreadBufferIncrement MutexThreadBufferIncrement.c -pthread
./MutexThreadBufferIncrement
```
