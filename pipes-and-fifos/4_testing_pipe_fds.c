#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <wait.h>


int
main(void)
{
    int mypipe[2];
    if (pipe(mypipe) == -1) {
        perror(NULL);
        exit(EXIT_FAILURE);
    }

    pid_t pid = fork();
    
    if (pid == 0) {
        /* Child process */
        printf("\n==== Child process ====\n");
        printf("Write End: %d\n", mypipe[1]);
        printf("Read End: %d\n", mypipe[0]);
    }
    else if (pid < 0) {
        perror(NULL);
        exit(EXIT_FAILURE);
    }
    else {
        wait(NULL);
        /* Parent process */
        printf("\n==== Parent process ====\n");
        printf("Write End: %d\n", mypipe[1]);
        printf("Read End: %d\n", mypipe[0]);
    }

    exit(EXIT_SUCCESS);
}