#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/wait.h>

#define ITERATIONS 10000

int main()
{
    int shmid;
    int *counter;

    // Create shared memory
    shmid = shmget(IPC_PRIVATE, sizeof(int),
                   IPC_CREAT | 0666);

    if (shmid == -1)
    {
        perror("shmget");
        exit(1);
    }

    // Attach
    counter = (int *)shmat(shmid, NULL, 0);

    if (counter == (void *)-1)
    {
        perror("shmat");
        exit(1);
    }

    *counter = 0;

    printf("Shared Memory Address: %p\n\n",
           (void *)counter);

    // P1
    pid_t p1 = fork();

    if (p1 == 0)
    {
        for (int i = 0; i < ITERATIONS; i++)
        {
            int temp = *counter;
            temp++;
            *counter = temp;
        }

        printf("P1 completed\n");
        exit(0);
    }

    // P2
    pid_t p2 = fork();

    if (p2 == 0)
    {
        for (int i = 0; i < ITERATIONS; i++)
        {
            int temp = *counter;
            temp++;
            *counter = temp;
        }

        printf("P2 completed\n");
        exit(0);
    }

    // Parent waits
    wait(NULL);
    wait(NULL);

    printf("\n----- WITHOUT SYNCHRONIZATION -----\n");

    printf("Expected Value : %d\n",
           2 * ITERATIONS);

    printf("Actual Value   : %d\n",
           *counter);

    // Cleanup
    shmdt(counter);
    shmctl(shmid, IPC_RMID, NULL);

    return 0;
}
 
