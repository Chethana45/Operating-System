#include <stdio.h>
#include <unistd.h>

int main()
{
    pid_t pid;

    pid = fork();

    if (pid == 0)
    {
        printf("I am a child\n");
        printf("Child PID: %d\n", getpid());
    }
    else
    {
        printf("I am a parent\n");
        printf("Parent PID: %d\n", getpid());
    }

    return 0;
}
