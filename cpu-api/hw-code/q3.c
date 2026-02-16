/**
 * Write another program using fork(). The child process should
 * print “hello”; the parent process should print “goodbye”. You should
 * try to ensure that the child process always prints first; can you do
 * this without calling wait() in the parent?
 * 
 * One method to do this: 
 *  A child process will send a SIGCHLD to the parent whenever it changes state.
 *  If everything goes right with the child process (simply printing), the parent
 *  will receive a SIGCHLD on the child's exit. We add a signal handler to catch
 *  the SIGCHLD and print the parent's message.
 * 
 * Another method to do this:
 *  We can use pipes to do inter-process communication. read(2) will block until
 *  data has been written to the pipe. So, we can block the parent until the child
 *  has written to the pipe. To get the correct, order, we print the child's message
 *  before having it write to the pipe. After the parent reads from the pipe, it
 *  can print its own message.
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

void sigchld_handler(int sig) {
    if (sig == SIGCHLD) {
        printf("goodbye");
    }
    exit(sig); 
}

int main_with_signals() {
    signal(SIGCHLD, sigchld_handler);

    int rc = fork();
    if (rc < 0) {
        fprintf(stderr, "Fork failed\n");
        return 1;
    } else if (rc == 0) {
        printf("hello");
    } else {
        // Parent: block and let the signal handler run when SIGCHLD is raised
        while(1);
    }
    return 0;
}

int main_with_pipe() {
    int pipe_fds[2]; 
    pipe(pipe_fds); // [r, w]

    int rc = fork();
    if (rc < 0) {
        fprintf(stderr, "Fork failed\n");
        return 1;
    } else if (rc == 0) {
        // Child: close read end, print, and write
        close(pipe_fds[0]);
        printf("hello");
        write(pipe_fds[1], "!\0", 2);
        close(pipe_fds[1]);
    } else {
        // Parent: close write end, print after reading
        close(pipe_fds[1]);
        char buf[2];
        int bytes_read = read(pipe_fds[0], buf, 2);
        if (bytes_read == 2) {
            printf("goodbye");
        }
        close(pipe_fds[0]);
    }
    return 0;
}

int main(int argc, char** argv) {
    // main_with_signals();
    main_with_pipe();
}