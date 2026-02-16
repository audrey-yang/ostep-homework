/**
 * Write a program that calls fork(). Before calling fork(),
 * have the main process access a variable (e.g., x) and set 
 * its value to something (e.g., 100). What value is the 
 * variable in the child process? What happens to the variable 
 * when both the child and parent change the value of x?
 * 
 * The value in the child process is its original value, 
 * as the child is a copy of parent without exec.
 * When both processes change its value, it get set to whatever the
 * process set it to. If the two processes set different values, 
 * we'll see they retain different values.
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char* argv[]) {
    int x = 100;

    int rc = fork();
    if (rc < 0) {
        fprintf(stderr, "Fork failed\n");
        return 1;
    } else if (rc == 0) {
        // With no change - expect original value
        // With change - expect change
        // x = 10;
        printf("Child (%d): x = %d\n", (int) getpid(), x);
    } else {
        // x = 20;
        printf("Parent (%d): x = %d\n", (int) getpid(), x);
    }

    return 0;
}
