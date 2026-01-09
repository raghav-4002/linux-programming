/*
    ioctl(term_fd, TIOCSCTTY) can be used to attach a new terminal with a
    session. The calling process should be a session leader. Making this
    call will detach any terminal association that the process previously
    had.
*/


#include <asm-generic/ioctls.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <stdio.h>
#include <stdlib.h>


void
print_details(void)
{
    printf("pid=%d   gid=%d   sid=%d\n", getpid(), getpgrp(), getsid(getpid()));
}


void
detach_terminal(void)
{
    int term_fd = open("/dev/tty", TIOCNOTTY);
    if (term_fd == -1) {
        perror("Terminal detach failed");
        _exit(EXIT_FAILURE);
    }
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
attach_terminal(void)
{
    /* Not sure how to do it tbh ;) */
}


void
handle_child_process(void)
{
    printf("\n===== Inside child process =====\n");
    printf("Before: ");
    print_details();

    detach_terminal();
    make_session_leader();
    attach_terminal();

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