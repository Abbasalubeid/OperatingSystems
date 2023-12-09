
## Reader-Writer Problem with Semaphores

The Reader-Writer problem is a classic example of a multi-process synchronization issue in operating systems. The problem involves managing access to a shared resource between multiple reader processes and a single writer process. The core challenge is to enable several readers to concurrently read the resource without interruption from a writing process, while ensuring a writer has undisturbed access when needed.

`reader_writer.c` showcases a solution to the Reader-Writer problem using POSIX semaphores and shared memory in C. It demonstrates synchronization between reader and writer processes to access a shared integer buffer while ensuring data integrity and consistency.

### Key Concepts
- **Atomicity**: Critical operations like updating the count of active readers must be atomic to prevent race conditions.
- **Semaphore Synchronization**: Two semaphores are used:
  - `rw_mutex`: Ensures that when a writer is writing, no readers can read.
  - `mutex`: Protects the `read_count` variable and ensures that updates to it are atomic.
- **Shared Memory**: A shared data structure is used to hold the `read_count` and the buffer variable.

### Problem Solution
- **Readers**: Increment `read_count`. If the count is 1 (i.e., it's the first reader), they wait on `rw_mutex` to block writers. After reading, they decrement `read_count`, and if it drops to 0 (i.e., the last reader), they signal `rw_mutex` to allow writers.
- **Writers**: Wait for `rw_mutex` to ensure no readers are currently reading and then proceed to write. Once done, they signal `rw_mutex` to allow readers or another writer.

### Usage
To compile and run the program:

```bash
gcc -o readerWriter reader_writer.c
./readerWriter
```
