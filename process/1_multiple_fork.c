#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>


#define SOME_NON_ZERO_NUM 1
#define COUNT             10

int
main(void)
{
    pid_t id = SOME_NON_ZERO_NUM;
    for (int i = 0; i < COUNT; i++) {
        if (id != 0) {
            id = fork();
            if (id == 0) {
                printf("Child %d\n", i);
                break;
            }
        }
    }

}