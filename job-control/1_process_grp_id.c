#include <unistd.h>
#include <stdio.h>


int
main(void)
{
    pid_t group_id;
    group_id = getpgrp();

    printf("Group id: %d\n", group_id);
}
