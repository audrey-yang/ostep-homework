/**
 * Write a slight modification of the previous program, this time using 
 * waitpid() instead of wait(). When would waitpid() be useful?
 * 
 * waitpid() is more flexible than wait(), as we can use it to wait for
 * specific children, all children, and without blocking.
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
    } else {
        int status;
        pid_t finished_pid = waitpid(rc, &status, 0);
        printf("Parent: Child %x finished with status %d\n", finished_pid, status);
    }
    return 0;
}