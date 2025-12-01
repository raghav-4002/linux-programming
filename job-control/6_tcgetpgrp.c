#include <unistd.h>
#include <sys/types.h>
#include <stdio.h>


int
main(void)
{
    pid_t current_process_gid = getpgrp();
    pid_t fg_process_gid = tcgetpgrp(2);

    printf("Process ID of this program: %d\n", current_process_gid);
    printf("Process ID of foreground process of terminal: %d\n", fg_process_gid);
}
