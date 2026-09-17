#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>
#include <sys/wait.h>

void handler(int sig)
{
    printf("Child received SIGUSR1 signal\n");
}

int main()
{
    pid_t pid;

    signal(SIGUSR1, handler);

    pid = fork();

    if (pid == 0)
    {
        printf("Child waiting for signal\n");
        pause();

        printf("Child pauses gracefully\n");
        exit(0);
    }
    else
    {
        sleep(5);

        printf("Parent sending SIGUSR1\n");
        kill(pid, SIGUSR1);

        wait(NULL);
    }

    return 0;
}
