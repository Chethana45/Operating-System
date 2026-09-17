#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <sys/wait.h>

#define ITERATIONS 10000

union semun
{
    int val;
};

// Wait / P operation
void wait_sem(int semid)
{
    struct sembuf operation;

    operation.sem_num = 0;
    operation.sem_op = -1;
    operation.sem_flg = 0;

    semop(semid, &operation, 1);
}

// Signal / V operation
void signal_sem(int semid)
{
    struct sembuf operation;

    operation.sem_num = 0;
    operation.sem_op = 1;
    operation.sem_flg = 0;

    semop(semid, &operation, 1);
}

int main()
{
    int shmid;
    int semid;
    int *counter;

    // --------------------------------
    // Create shared memory
    // --------------------------------

    shmid = shmget(IPC_PRIVATE, sizeof(int),
                   IPC_CREAT | 0666);

    if (shmid == -1)
    {
        perror("shmget");
        exit(1);
    }

    counter = (int *)shmat(shmid, NULL, 0);

    if (counter == (void *)-1)
    {
        perror("shmat");
        exit(1);
    }

    *counter = 0;

    // --------------------------------
    // Create semaphore
    // --------------------------------

    semid = semget(IPC_PRIVATE, 1,
                   IPC_CREAT | 0666);

    if (semid == -1)
    {
        perror("semget");
        exit(1);
    }

    union semun arg;
    arg.val = 1;

    semctl(semid, 0, SETVAL, arg);

    printf("Shared Memory Address: %p\n",
           (void *)counter);

    // --------------------------------
    // P1
    // --------------------------------

    pid_t p1 = fork();

    if (p1 == 0)
    {
        for (int i = 0; i < ITERATIONS; i++)
        {
            // Enter critical section
            wait_sem(semid);

            (*counter)++;

            // Exit critical section
            signal_sem(semid);
        }

        printf("P1 completed\n");
        exit(0);
    }

    // --------------------------------
    // P2
    // --------------------------------

    pid_t p2 = fork();

    if (p2 == 0)
    {
        for (int i = 0; i < ITERATIONS; i++)
        {
            // Enter critical section
            wait_sem(semid);

            (*counter)++;

            // Exit critical section
            signal_sem(semid);
        }

        printf("P2 completed\n");
        exit(0);
    }

    // Parent waits
    wait(NULL);
    wait(NULL);

    printf("\n----- WITH SYNCHRONIZATION -----\n");

    printf("Expected Value : %d\n",
           2 * ITERATIONS);

    printf("Actual Value   : %d\n",
           *counter);

    // Cleanup
    shmdt(counter);

    shmctl(shmid, IPC_RMID, NULL);

    semctl(semid, 0, IPC_RMID);

    return 0;
}
