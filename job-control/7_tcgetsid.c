#include <fcntl.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <termios.h>
#include <stdio.h>


int
main(void)
{
    /* `tcgetsid(int fd)` is used to retrieve the session id of the
       session which is currently using the terminal specified by `fd` . */

    /* To get `fd`, we can use the `open()` syscall */

    int term_fd = open("/dev/tty", O_RDWR);
    if (term_fd == -1) {
        perror("Failure to open terminal");
        exit(EXIT_FAILURE);
    }

    pid_t sid = tcgetsid(term_fd);
    if (sid == -1) {
        perror("Retrieving session id");
        exit(EXIT_FAILURE);
    }

    printf("Terminal fd: %d\n", term_fd);
    printf("Session id: %u\n", sid);

    exit(EXIT_SUCCESS);
}