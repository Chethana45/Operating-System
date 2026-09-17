#include <stdio.h>
#include <unistd.h>

int main()
{
    char *args[] = {"pwd", NULL};

    execvp("pwd", args);

    return 0;
}
