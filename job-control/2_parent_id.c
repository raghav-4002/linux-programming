#include <unistd.h>
#include <stdio.h>


int
main(void)
{
    pid_t parent_pid = getppid();
    pid_t parent_gid = getpgid(parent_pid);
    pid_t parent_sid = getsid(parent_pid);

    /* All three below must be same as parent(shell)
        is the group leader and session leader, meaning
        both must be equal to pid */
    printf("Parent's process id: %d\n", parent_pid);
    printf("Parent's group id: %d\n", parent_gid);
    printf("Parent's session id: %d\n", parent_sid);
}
