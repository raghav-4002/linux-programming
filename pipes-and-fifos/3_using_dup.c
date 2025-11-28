#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>


void
read_from_pipe(int fd)
{
    /* We need to execute grep thus set
      stdin to reading end of pipe */
    dup2(fd, STDIN_FILENO);
    system("grep 1");
}


void
write_to_pipe(int fd)
{
    /* We need to execute ls thus set
       stdout to writing end of pipe */
    dup2(fd, STDOUT_FILENO);
    system("ls");
}


int
main(void)
{
    int filedes[2];
    if (pipe(filedes) == -1) {
        fprintf(stderr, "Pipe creation failed...\n");
        return EXIT_FAILURE;
    }

    pid_t pid = fork();

    if (pid == 0) {
        /* Inside child process. */
        close(filedes[1]);
        read_from_pipe(filedes[0]);
    }
    else if (pid < 0) {
        fprintf(stderr, "Fork failed\n");
        return EXIT_FAILURE;
    }
    else {
        /* Inside parent process */
        close(filedes[0]);
        write_to_pipe(filedes[1]);
    }
}
