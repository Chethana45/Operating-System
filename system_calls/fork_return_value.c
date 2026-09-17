#include <stdio.h>
#include <unistd.h>

int main()
{
    pid_t pid;

    pid = fork();

    if (pid == 0)
    {
        printf("Child: fork() returned 0\n");
        printf("Child PID: %d\n", getpid());
    }
    else
    {
        printf("Parent: fork() returned %d\n", pid);
        printf("Parent PID: %d\n", getpid());
    }

    return 0;
}
