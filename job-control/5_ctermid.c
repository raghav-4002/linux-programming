#include <stdio.h>


int
main(void)
{
    char *ttyname;
    printf("ttyname: %s\n", ctermid(NULL));
}
