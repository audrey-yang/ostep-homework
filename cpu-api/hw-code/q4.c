/**
 * Write a program that calls fork() and then calls some form of
 * exec()to run the program /bin/ls. See if you can try all of the
 * variants of exec(), including (on Linux) execl(), execle(),
 * execlp(), execv(), execvp(), and execvpe(). Why do
 * you think there are so many variants of the same basic call?
 * 
 * First thoughts
 * - e: allow some flexibility with setting or inheriting env
 * - p: allow easy use of same executables as command line when precise location
 *      may be unknown or very long
 * - l/v: v is probably for compatability with argv. l might have been the original
 *      way when we know exactly what the child needs to run.
 * 
 * After referencing the internet, seems like more functions were added as the need arose
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
        /* execl: full path of executable + list of args to pass on */
        printf("execl\n");
        execl("/bin/ls", "ls", "-l", (char *) NULL);
        /* execlp: execl with executable name only - will search PATH */
        // printf("execlp\n");
        // execlp("ls", "ls", "-l", (char *) NULL);

        char *ls_cmd[] = { "ls", "-l", (char *) NULL };
        /* execv: full path of executable + array of args to pass on */
        // printf("execv\n");
        // execv("/bin/ls", ls_cmd);
        /* execvp: execvp with executable name only - will search PATH */
        // printf("execvp\n");
        // execvp("ls", ls_cmd);
        

        char *env[] = { "VAR=x", "GREETING=hello", (char *) NULL };
        /* execle: execl with env array */
        // printf("execle\n");
        // execle ("/usr/bin/env", "env", "-0", (char *)0, env);
        /* execve: execv with env array */
        // char *env_cmd[] = { "env", "-0", (char *) NULL };
        // printf("execve\n");
        // execve("/usr/bin/env", env_cmd, env);
        /* execvpe: execvp with env array (GNU extension) */
        // printf("execvpe\n");
        // execvpe("ls", env_cmd, env);
    } else {
        wait(NULL);
        printf("Child finished\n");
    }
    return 0;
}