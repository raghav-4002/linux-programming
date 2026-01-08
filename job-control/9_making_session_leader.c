/*
    setsid() can be used to make the calling process a session leader.
    This leads to creation of a new session of which the calling process
    becomes the session leader of. Any association with previous controlling
    terminal is broken. The process is also made the group leader of the
    group in the newly created session.
    For setsid() to work, the calling process shouldn't be a group leader.
*/

#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>


void
print_details(void)
{
    printf("pid=%d   gid=%d   sid=%d\n", getpid(), getpgrp(), getsid(getpid()));
}


void
make_session_leader(void)
{
    if (setsid() == -1) {
        perror("Making session leader failed");
        _exit(EXIT_FAILURE);
    }
}


void
handle_child_process(void)
{
    printf("\n===== Inside child process =====\n");
    printf("Before: ");
    print_details();

    make_session_leader();
    printf("After: ");
    print_details();
}


int
main(void)
{
    int pid = fork();
    if (pid == 0) {
        /* Child process */
        handle_child_process();
        printf("\n----- Child exiting -----\n");
    }
    else if (pid == -1) {
        perror("Fork failed");
        exit(EXIT_FAILURE);
    }
    else {
        /* Parent process */
        wait(NULL);
        printf("\n===== Inside parent process =====\n");
        print_details();
        printf("\n----- Parent exiting -----\n");
    }

    exit(EXIT_SUCCESS);
}