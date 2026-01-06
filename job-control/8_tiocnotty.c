/*
    ioctl(fd, TIOCNOTTY) can be used to remove association
    of a process with its controlling terminal. Subsequent
    attempts to open the file "/dev/tty" will fail.
*/

#include <stdlib.h>
#include <sys/ioctl.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>


void
get_details(void)
{
    printf("pid: %u   gid: %u   sid: %u\n", 
            getpid(), getpgrp(), getsid(getpid()));
}


void
detach_terminal(void)
{
    int term_fd = open("/dev/tty", O_RDWR);
    if (ioctl(term_fd, TIOCNOTTY) == -1) {
        perror("Terminal detach error");
        _exit(EXIT_FAILURE);
    }
}


void
open_terminal(void)
{
    int term_fd = open("/dev/tty", O_RDWR);
    if (term_fd == -1) {
        perror("Trying to reopen terminal failed");
    }
    else {
        printf("Terminal was opened successfully\n");
    }
}


int
main(void)
{
    if (fork() == 0) {
        /* Inside child process */
        printf("\n===== Inside child process =====\n");
        printf("Before terminal disconnect: ");
        get_details();
        
        detach_terminal();

        printf("After terminal disconnect: ");
        get_details();

        /* Attempt to open terminal; should fail */
        open_terminal();
    }
    else {
        wait(NULL);
        /* Ignoring error (inside parent process) */
        printf("\n===== Inside parent process =====\n");
        printf("Details: ");
        get_details();
        
        /* Attempt to open terminal; should succeed */
        open_terminal();
    }

    return 0;
}