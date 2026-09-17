#include <stdio.h>
#include <unistd.h>

int main()
{
    fork();
    printf("HI\n");

    fork();
    printf("Hello\n");

    fork();
    printf("welcome\n");

    return 0;
}
