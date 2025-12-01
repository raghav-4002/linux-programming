#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>


int
main(void)
{
    /* Current process */
    pid_t pid = getpid();
    pid_t gid = getpgid(pid);
    pid_t sid = getsid(0);

    /* Parent process (shell) */
    pid_t ppid = getppid();
    pid_t pgid = getpgid(ppid);
    pid_t psid = getsid(ppid);

    printf("Process Id of current process: %d\n", pid);
    printf("Group ID of current process: %d\n", gid);
    printf("Session ID of current process: %d\n", sid);

    printf("Process Id of parent process: %d\n", ppid);
    printf("Group ID of parent process: %d\n", pgid);
    printf("Session ID of parent process: %d\n", psid);

    printf("\n...Insights...\n");
    printf("Session Id of both the parent and current prcocess must be same\n");
    printf("Group ID of both parent and current process must be different\n");
    printf("Group ID and process ID of process must be same as it is the current group leader...\n");
    printf("Group ID and process ID of parent must also be same\n");
    printf("Session ID, group ID and process ID of the parent must be same as it is the session master...\n");

    return 0;
}
