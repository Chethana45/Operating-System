#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>

int main()
{
    pid_t p1, p2;

    printf("P0: PID = %d, PPID = %d\n", getpid(), getppid());

    p1 = fork();

    if (p1 == 0)
    {
        printf("P1: PID = %d, PPID = %d\n", getpid(), getppid());
        exit(0);
    }

    p2 = fork();

    if (p2 == 0)
    {
        printf("P2: PID = %d, PPID = %d\n", getpid(), getppid());
        exit(0);
    }

    wait(NULL);
    wait(NULL);

    printf("P0: Both children completed\n");

    return 0;
}
