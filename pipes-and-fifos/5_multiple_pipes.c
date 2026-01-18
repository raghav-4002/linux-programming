#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>


void
launch_command(char **cmd, int infile, int outfile)
{
    if (infile != STDIN_FILENO) {
        if (dup2(infile, STDIN_FILENO) == -1) {
            perror("dup");
            _exit(EXIT_FAILURE);
        }
        close(infile);
    }

    if (outfile != STDOUT_FILENO) {
        if (dup2(outfile, STDOUT_FILENO) == -1) {
            perror("dup");
            _exit(EXIT_FAILURE);
        }
        close(outfile);
    }

    execvp(cmd[0], cmd);
    perror("execvp");
    _exit(EXIT_FAILURE);
}


int
main(void)
{
    char *c1[] = {"ls", "-al", NULL};
    char *c2[] = {"grep", "e", NULL};
    char *c3[] = {"rev", NULL};
    char *c4[] = {"sort", NULL};
    char **cmd[] = {c1, c2, c3, c4};

    int count = sizeof(cmd) / sizeof(cmd[1]);
    int pipefd[2];
    int infile = STDIN_FILENO;
    int outfile;

    for (int i = 0; i < count; i++) {
        if (i + 1 == count) {
            outfile = STDOUT_FILENO;
        }
        else {
            if (pipe(pipefd) < 0) {
                perror("Pipe");
                exit(EXIT_FAILURE);
            }
            outfile = pipefd[1];
        }

        pid_t pid = fork();
        if (pid == 0) {
            launch_command(cmd[i], infile, outfile);
        }
        else if (pid == -1) {
            perror("fork");
            exit(EXIT_FAILURE);
        }
        else {
            if (infile != STDIN_FILENO) {
                close(infile);
            }
            if (outfile != STDOUT_FILENO) {
                close(outfile);
            }
            infile = pipefd[0];
        }
    }
}