#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>


/* If we redirect the output of this program to a file, ./a.out > file, 
    `Ciao` will appear before `Hello, world`. This is because, redirecting
    to files is not line-buffered, meaning that the call to printf buffers
    the hello, world string, but the call to Ciao isn't buffered and its
    written first into the file. When the program exits, the buffered output
    is flushed automatically and thus appears after ciao. */
int
main(void)
{
    printf("Hello, world\n");
    write(STDOUT_FILENO, "Ciao\n", 5);
}