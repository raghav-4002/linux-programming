#include <stdio.h>
#include <unistd.h>


#define SOME_NUMBER 1313


int
main(void)
{
    /*
     * Isn't working for me
     */

    pid_t process_id  = getpid();
    pid_t process_gid = getpgrp();

    printf("==== Before changing gid ====\n");
    printf("Process id: %d\n", process_id);
    printf("Process group id: %d\n", process_gid);

    /* changing the group id of current process */
    if (setgid(SOME_NUMBER) == -1 ) {
        perror("\nError");
        return 1;
    }
    process_id  = getpid();
    process_gid = getpgrp();

    printf("\n==== After changing gid ====\n");
    printf("Process id: %d\n", process_id);
    printf("Process group id: %d\n", process_gid);
}
