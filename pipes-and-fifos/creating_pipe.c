#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>


void
read_from_pipe(int filedes[])
{
    /* Reading from the pipe */
    char arr[100];
    read(filedes[0], arr, sizeof(arr));
    printf("Reading from the reading process: %s\n", arr);

    // /* Writing to the same pipe */
    // char buf[] = "Nigga balls";
    // write(filedes[1], buf, sizeof(buf));
}


void
write_to_pipe(int filedes[])
{
    /* Writing to pipe */
    char buf[] = "Hello, friend";
    write(filedes[1], buf, sizeof(buf));

    // /* Reading from the same pipe */
    // char arr[100];
    // read(filedes[0], arr, sizeof(arr));
    // printf("Trying to read from the writing process: %s\n", arr);
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
        // close(filedes[1]);
        read_from_pipe(filedes);
    }
    else if (pid < 0) {
        /* Error forking */
        fprintf(stderr, "Error forking\n");
        return EXIT_FAILURE;
    }
    else {
        /* Inside parent process
           Close the read end of pipe */
        // close(filedes[0]);
        write_to_pipe(filedes);
    }
}
