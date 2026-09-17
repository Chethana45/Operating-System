#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>

int main()
{
    pid_t pid1, pid2;

    pid1 = fork();

    if (pid1 == 0)
    {
        execlp("ls", "ls", NULL);
        exit(0);
    }

    pid2 = fork();

    if (pid2 == 0)
    {
        execlp("pwd", "pwd", NULL);
        exit(0);
    }

    wait(NULL);
    wait(NULL);

    printf("Parent: Both children are completed\n");

    return 0;
}
