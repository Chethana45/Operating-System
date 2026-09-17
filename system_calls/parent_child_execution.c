#include <stdio.h>
#include <unistd.h>

int main()
{
    pid_t pid;

    pid = fork();

    if (pid == 0)
    {
        for (int i = 6; i <= 10; i++)
        {
            printf("Child: %d\n", i);
        }
    }
    else
    {
        for (int i = 1; i <= 5; i++)
        {
            printf("Parent: %d\n", i);
        }
    }

    return 0;
}
