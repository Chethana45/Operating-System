#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main()
{
    pid_t pid;

    pid = fork();

    if (pid == 0)
    {
        execlp("date", "date", NULL);
    }
    else
    {
        wait(NULL);
        printf("Parent: child terminates\n");
    }

    return 0;
}
