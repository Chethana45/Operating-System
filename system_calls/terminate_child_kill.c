#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>

int main()
{
    pid_t pid;

    pid = fork();

    if (pid == 0)
    {
        printf("Child running continuously...\n");

        while (1)
        {
            sleep(1);
        }
    }
    else
    {
        printf("Parent waiting for 10 seconds...\n");

        sleep(10);

        printf("Parent terminating child...\n");

        kill(pid, SIGTERM);

        wait(NULL);

        printf("Child terminated\n");
    }

    return 0;
}
