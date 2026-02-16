/**
 * Write a program that opens a file (with the open() system call)
 * and then calls fork() to create a new process. Can both the child
 * and parent access the file descriptor returned by open()? What
 * happens when they are writing to the file concurrently, i.e., at the
 * same time?
 * 
 * The child and parent can both access the file descriptor returns by
 * open (the child inherits these from the parent per specifications
 * of `fork`). In my tests below, it looks like the child and parent 
 * can both write to the file, with the output of both ending up in
 * the file, even if O_TRUNC is specified.
 * 
 * > cat q2.txt
 * > HEY THEREHello, world
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

int main(int argc, char* argv[]) {
    int fd = open("./q2.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);

    int rc = fork();
    if (rc < 0) {
        fprintf(stderr, "Fork failed\n");
        return 1;
    } else if (rc == 0) {
        int bytes_written = write(fd, "Hello, world", 12);
        printf("Child (%d) wrote %d bytes\n", (int) getpid(), bytes_written);
    } else {
        int bytes_written = write(fd, "HEY THERE", 9);
        printf("Parent (%d) wrote %d bytes\n\n", (int) getpid(), bytes_written);
    }
    return 0;
}
