#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>


void
read_from_pipe(int fd)
{
    /* Reading data from the pipe thru. the
       output side */
    char buf[100];
    read(fd, buf, sizeof(buf));

    printf("Reading from the child process: %s\n", buf);

    /* Its a good practice to close unused file descriptors */
    close(fd);
}


void
write_to_pipe(int fd)
{
    /* Writing buffer into the pipe thru. the 
       input side */
    char buf[] = "Hi from the parent process...";
    write(fd, buf, sizeof(buf));
    close(fd);
}


int
main(void)
{
    int filedes[2];
    if (pipe(filedes) == -1) {
        fprintf(stderr, "Pipe can't be created\n");
        return EXIT_FAILURE;
    }

    pid_t pid = fork();

    if(pid == 0) {
        /* Inside child process (reads from pipe) */
        close(filedes[1]);
        read_from_pipe(filedes[0]);
    }
    else if (pid < 0) {
        fprintf(stderr, "Forking failed\n");
        return EXIT_FAILURE;
    }
    else {
        /* Inside parent process (writes to pipe) */
        close(filedes[0]);
        write_to_pipe(filedes[1]);
    }

    return EXIT_SUCCESS;
}
