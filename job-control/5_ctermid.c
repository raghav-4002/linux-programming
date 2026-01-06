#include <stdio.h>


int
main(void)
{
    printf("ttyname: %s\n", ctermid(NULL));
}
