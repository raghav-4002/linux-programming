#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>


int
main(void)
{
    pid_t pid;
    int filedes[2];

    /* Create a pipe */
    pipe(filedes);

    /* Create a child process */
    pid = fork();
    if (pid == 0) {
        /* Inside child process
           Close the write end of pipe */
        close(filedes[1]);
    }
    else if (pid < 0) {
        /* Error forking */
        fprintf(stderr, "Error forking\n");
        return EXIT_FAILURE;
    }
    else {
        /* Inside parent process
           Close the read end of pipe */
        close(filedes[0]);
    }
}
