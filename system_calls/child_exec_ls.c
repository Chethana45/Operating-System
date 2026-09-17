#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main()
{
    pid_t pid;

    pid = fork();

    if (pid == 0)
    {
        printf("Child process with ls -l:\n");
        execlp("ls", "ls", "-l", NULL);
    }
    else
    {
        wait(NULL);
        printf("Parent process is executed after child\n");
    }

    return 0;
}
