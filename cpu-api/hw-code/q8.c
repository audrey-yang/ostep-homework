/**
 * Write a program that creates two children, and connects the 
 * standard output of one to the standard input of the other, 
 * using the pipe() system call.
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

int main(int argc, char** argv) {
    int fds[2]; // [r, w]
    pipe(fds);

    pid_t pid1 = fork();
    if (pid1 < 0) {
        fprintf(stderr, "Fork failed\n");
        return 1;
    } else if (pid1 == 0) {
        // Child 1: writing
        close(fds[0]);
        dup2(fds[1], STDOUT_FILENO);
        printf("%x (child 1): Hello, sibling!", getpid());
        return 0;
    }


    pid_t pid2 = fork();
    if (pid2 < 0) {
        fprintf(stderr, "Fork failed\n");
        return 1;
    } else if (pid2 == 0) {
        // Child 2: reading
        close(fds[1]);
        dup2(fds[0], STDIN_FILENO);
        char buf[64];
        if (read(STDIN_FILENO, buf, 64) < 0) {
            perror("read");
        }
        printf("%x (child 2): Got a message: \"%s\"\n", getpid(), buf);
        return 0;
    } 

    int status;
    pid_t finished_pid;
    while ((finished_pid = waitpid(-1, &status, 0)) > 0) {
        printf("%x (parent): Child %x finished with status %d\n", getpid(), finished_pid, status);
    }

    return 0;
}