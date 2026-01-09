#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>


#define COUNT 10

int
main(void)
{
    for (int i = 0; i < COUNT; i++) {
        if (fork() == 0) {
            printf("Child %d\n", i);
            break;
        }
    }

}