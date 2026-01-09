#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>


void
send_msg_thru_pipe(int *mypipe, int i)
{
    if (i == 0) {
        close(mypipe[0]);
        char buf[] = "Message from child 1";
        write(mypipe[1], buf, sizeof(buf));
    } else {
        close(mypipe[1]);
        char buf[128];
        read(mypipe[0], buf, sizeof(buf));

        printf("Message from child2: %s\n", buf);
    }
}


#define COUNT 2

int
main(void)
{
    int mypipe[2];
    if (pipe(mypipe) == -1) {
        perror(NULL);
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < COUNT; i++) {
        if (fork() == 0) {
            send_msg_thru_pipe(mypipe, i);
            break;
        }
    }

}