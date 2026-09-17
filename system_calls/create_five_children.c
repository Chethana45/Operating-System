#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>

int main()
{
    pid_t pid;

    for (int i = 1; i <= 5; i++)
    {
        pid = fork();

        if (pid == 0)
        {
            printf("Child %d: PID = %d\n", i, getpid());
            exit(0);
        }
    }

    for (int i = 0; i < 5; i++)
    {
        wait(NULL);
    }

    printf("Parent: All children completed\n");

    return 0;
}
