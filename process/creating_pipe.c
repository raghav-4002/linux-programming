#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>


void
read_from_pipe(int filedes)
{
    /* Read from pipe and store to buffer */
    char buf[100];
    read(filedes, buf, sizeof(buf));
    printf("%s", buf);
}


void
write_to_pipe(int filedes)
{
    /* Write buffer into the pipe */
    char buf[] = "hello, friend";
    int n = sizeof(buf);
    write(filedes, buf, n);
}


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
        read_from_pipe(filedes[0]);
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
        write_to_pipe(filedes[1]);
    }
}
