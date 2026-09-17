


 #include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

int main()
{
    int pipe1[2];   // P1 -> P2
    int pipe2[2];   // P2 -> P1

    // Create two pipes
    pipe(pipe1);
    pipe(pipe2);

    // Create child process
    pid_t pid = fork();

    if (pid == 0)
    {
        // =========================
        // CHILD PROCESS - P2
        // =========================

        char message[100];

        // P2 only reads from pipe1
        close(pipe1[1]);

        // P2 only writes to pipe2
        close(pipe2[0]);

        // Receive message from P1
        read(pipe1[0], message, sizeof(message));

        printf("P2 received: %s\n", message);

        // Send reply to P1
        strcpy(message, "Hello P1, message received!");

        write(pipe2[1], message, strlen(message) + 1);

        // Close used pipe ends
        close(pipe1[0]);
        close(pipe2[1]);
    }
    else
    {
        // =========================
        // PARENT PROCESS - P1
        // =========================

        char message[100];

        // P1 only writes to pipe1
        close(pipe1[0]);

        // P1 only reads from pipe2
        close(pipe2[1]);

        // Send message to P2
        strcpy(message, "Hello P2, this is P1!");

        write(pipe1[1], message, strlen(message) + 1);

        // Receive reply from P2
        read(pipe2[0], message, sizeof(message));

        printf("P1 received: %s\n", message);

        // Close used pipe ends
        close(pipe1[1]);
        close(pipe2[0]);

        // Wait for child
        wait(NULL);
    }

    return 0;
}
