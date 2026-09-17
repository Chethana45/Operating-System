#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>

int main()
{
    pid_t p1, p2;

    p1 = fork();

    if (p1 == 0)
    {
        execlp("date", "date", NULL);
        exit(0);
    }

    p2 = fork();

    if (p2 == 0)
    {
        execlp("pwd", "pwd", NULL);
        exit(0);
    }

    int status;

    waitpid(p1, &status, 0);
    printf("Child 1 terminated first\n");

    waitpid(p2, &status, 0);
    printf("Child 2 terminated second\n");

    return 0;
}
