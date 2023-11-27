## Inter-Process Communication in C Using pipes

In the realm of Unix-like systems, creating and managing processes is a fundamental aspect of system programming. This lab focuses on the practical implementation of process control and inter-process communication (IPC) using system calls like `fork`, `exec`, `wait`, and `pipe` in C. The objective is to simulate the execution of the Unix command `ls / | wc -l`, which counts the number of files and directories in the root path.

### Key Concepts

- **Process Creation with `fork()`**: The `fork()` system call is used to create a new process by duplicating the current process. The child process runs concurrently with the parent, and `fork()` returns a different value in each process (0 in the child and the child's PID in the parent).
- **Executing Commands with `exec()`**: The `exec()` family of functions replaces the current process image with a new process image, executing a different program. In this lab, `execlp()` is used to execute `ls` and `wc` commands.
- **Communication via `pipe()`**: A pipe is a unidirectional communication channel used for IPC. The `pipe()` system call creates a pipe with two file descriptors: one for reading and one for writing.

### Implementation Details

1. **Pipe Creation**: A pipe is created using `pipe(pipe_ends)`, where `pipe_ends` is an array of two integers. The first integer (`pipe_ends[0]`) is for reading, and the second (`pipe_ends[1]`) is for writing.

2. **Process Duplication**: The parent process creates a child process using `fork()`. The child process then executes the `ls /` command, and its output is written to the pipe. The parent process waits for the child to complete, reads from the pipe, and executes the `wc -l` command to count the lines.

3. **Standard I/O Redirection**: In the child process, the standard output is redirected to the pipe's write end using `dup2()`. In the parent process, the standard input is redirected to the pipe's read end, allowing the output of `ls` to be used as input for `wc`.

### Usage

Compile and run the program:

```bash
gcc -o ProcessPipeCommunication ProcessPipeCommunication.c
./ProcessPipeCommunication
```

To verify the correctness of the program's output, run the actual Unix command in the terminal (applicable on Unix-like systems such as Linux or macOS). Execute the following command:

```bash
ls / | wc -l
```

This command will display the number of files and directories in the root path which should match the output of the `ProcessPipeCommunication` program.