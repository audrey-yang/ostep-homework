/**
 * Now write a program that uses wait()to wait for the child process
 * to finish in the parent. What does wait() return? What happens if
 * you use wait() in the child?
 * 
 * wait() returns the pid of the child that just finished. If we use
 * wait() in the child, it will return -1 for the ECHILD error as
 * specified in the man pages.
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
        printf("Child: I am the child\n");
        pid_t finished_pid = wait(NULL);
        if (finished_pid < 0) {
            perror("wait");
        } else {
            printf("Child: Grandchild %x finished\n", finished_pid);
        }
    } else {
        int status;
        pid_t finished_pid = wait(&status);
        printf("Parent: Child %x finished with status %d\n", finished_pid, status);
    }
    return 0;
}