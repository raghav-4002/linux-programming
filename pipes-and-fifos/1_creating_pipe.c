#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>


int
main(void)
{
    int filedes[2];

    /* Create the pipe */
    if (pipe(filedes) == -1) {
        fprintf(stderr, "Pipe creation failed\n");
        return EXIT_FAILURE;
    }

    /* Create a child process */
    pid_t pid = fork();

    if (pid == 0) {
        /* Inside the child process.
           Close the write end of the pipe
           if we want to read. */
        close(filedes[1]);
    }
    else if (pid < 0) {
        /* fork failed */
        fprintf(stderr, "fork failed\n");
        return EXIT_FAILURE;
    }
    else {
        /* Inside the parent process.
           Close the read end of the pipe
           if we want to write */
        close(filedes[0]);
    }

    return EXIT_SUCCESS;
}
