/**
 * Write a program that creates a child process, and then in the child
 * closes standard output (STDOUT_FILENO). What happens if the child
 * calls printf() to print some output after closing the descriptor?
 * 
 * If the child calls printf() after closing STDOUT_FILENO, it will
 * set the ERRNO as EBADF.
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

int main(int argc, char** argv) {
    int rc = fork();
    if (rc < 0) {
        fprintf(stderr, "Fork failed\n");
        return 1;
    } else if (rc == 0) {
        close(STDOUT_FILENO);
        printf("Does this work?\n");
        perror("printf");
    } else {
        int status;
        pid_t finished_pid = waitpid(rc, &status, 0);
        printf("Parent: Child %x finished with status %d\n", finished_pid, status);
    }
    return 0;
}