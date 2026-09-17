#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

int main()
{
    pid_t pid;

    for (int i = 1; i <= 3; i++)
    {
        pid = fork();

        if (pid == 0)
        {
            printf("Child %d: PID = %d, PPID = %d\n",
                   i, getpid(), getppid());
            exit(0);
        }
    }

    for (int i = 0; i < 3; i++)
    {
        wait(NULL);
    }

    printf("Parent: PID = %d\n", getpid());

    return 0;
}
