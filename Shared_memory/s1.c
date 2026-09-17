#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/wait.h>

#define SIZE 5

int main()
{
    int shmid;
    int *shm;

    // Create shared memory
    shmid = shmget(IPC_PRIVATE, SIZE * sizeof(int),
                   IPC_CREAT | 0666);

    if (shmid == -1)
    {
        perror("shmget");
        exit(1);
    }

    // Attach shared memory
    shm = (int *)shmat(shmid, NULL, 0);

    if (shm == (void *)-1)
    {
        perror("shmat");
        exit(1);
    }

    // Initialize
    for (int i = 0; i < SIZE; i++)
        shm[i] = 0;

    printf("Shared Memory ID : %d\n", shmid);
    printf("Start Address    : %p\n", (void *)&shm[0]);
    printf("End Address      : %p\n", (void *)&shm[SIZE - 1]);
    printf("Segment Size     : %ld bytes\n\n",
           SIZE * sizeof(int));

    // Create P1
    pid_t p1 = fork();

    if (p1 == 0)
    {
        printf("P1 Address: %p\n", (void *)shm);

        // P1 writes
        shm[0] = 100;
        shm[1] = 200;

        printf("P1 wrote: %d %d\n", shm[0], shm[1]);

        exit(0);
    }

    wait(NULL);

    // Create P2
    pid_t p2 = fork();

    if (p2 == 0)
    {
        printf("P2 Address: %p\n", (void *)shm);

        // P2 reads P1's data
        printf("P2 read: %d %d\n", shm[0], shm[1]);

        // P2 writes
        shm[2] = shm[0] + shm[1];

        printf("P2 calculated: %d\n", shm[2]);

        exit(0);
    }

    wait(NULL);

    printf("\nFinal Shared Memory:\n");

    for (int i = 0; i < SIZE; i++)
        printf("shm[%d] = %d\n", i, shm[i]);

    // Detach
    shmdt(shm);

    // Remove shared memory
    shmctl(shmid, IPC_RMID, NULL);

    return 0;
}
