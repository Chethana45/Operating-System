#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main()
{
    pid_t pid;

    pid = fork();

    if (pid == 0)
    {
        printf("Child process is executing\n");
        printf("Child PID: %d\n", getpid());
    }
    else
    {
        wait(NULL);
        printf("I will execute after the child\n");
    }

    return 0;
}
