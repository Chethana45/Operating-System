#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main()
{
    pid_t pid;

    pid = fork();

    if (pid == 0)
    {
        printf("Child started\n");
        sleep(5);
        printf("Child completed after 5 seconds\n");
    }
    else
    {
        wait(NULL);
        printf("Parent executed after child\n");
    }

    return 0;
}
