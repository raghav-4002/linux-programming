#include <stdio.h>
#include <unistd.h>
#include <signal.h>


void
handler(int num)
{
    printf("I ain't gonna stop!!!\n");
}

int 
main(void)
{
    signal(SIGINT, handler);
    while (1) {
        printf("Doing nothing (pid: %d)\n", getpid());
        sleep(1);
    }
}