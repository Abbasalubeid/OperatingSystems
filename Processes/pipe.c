#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(void) {
    int pipe_ends[2]; // Array to hold the two ends of the pipe
    pid_t pid;

    if (pipe(pipe_ends) == -1) { // Create a pipe
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    pid = fork(); // Create a new child process

    if (pid == -1) {
        perror("fork"); // If fork fails, print error and exit
        exit(EXIT_FAILURE);
    }

    if (pid == 0) { 
        // Child process
        close(pipe_ends[0]); // Close unused read end of the pipe
        dup2(pipe_ends[1], STDOUT_FILENO); // Redirect standard output to pipe's write end
        execlp("ls", "ls", "/", NULL); // Execute ls command
    } else { 
        // Parent process
        close(pipe_ends[1]); // Close unused write end of the pipe
        wait(NULL); // Wait for child process to finish
        dup2(pipe_ends[0], STDIN_FILENO); // Redirect standard input to pipe's read end
        execlp("wc", "wc", "-l", NULL); // Execute wc command
    }

    return 0;
}
