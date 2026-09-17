#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>

int count = 0;

void handler(int sig)
{
    count++;

    printf("\nSIGINT received %d time(s)\n", count);

    if (count == 3)
    {
        printf("SIGINT received 3 times. Terminating...\n");
        exit(0);
    }
}

int main()
{
    signal(SIGINT, handler);

    printf("Press Ctrl+C three times\n");

    while (1)
    {
        pause();
    }

    return 0;
}
