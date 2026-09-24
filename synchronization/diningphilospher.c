#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>

#define N 5

pthread_mutex_t forks[N];
sem_t room;

int choice;

void *philosopher(void *arg)
{
    int id = *(int *)arg;

    int left = id;
    int right = (id + 1) % N;

    int first, second;

    /* Solution 1: Semaphore */
    if (choice == 1)
    {
        sem_wait(&room);

        pthread_mutex_lock(&forks[left]);
        pthread_mutex_lock(&forks[right]);

        printf("P%d is eating\n", id);

        pthread_mutex_unlock(&forks[right]);
        pthread_mutex_unlock(&forks[left]);

        sem_post(&room);
    }

    /* Solution 2: Resource Ordering */
    else if (choice == 2)
    {
        if (left < right)
        {
            first = left;
            second = right;
        }
        else
        {
            first = right;
            second = left;
        }

        pthread_mutex_lock(&forks[first]);
        pthread_mutex_lock(&forks[second]);

        printf("P%d is eating\n", id);

        pthread_mutex_unlock(&forks[second]);
        pthread_mutex_unlock(&forks[first]);
    }

    /* Solution 3: Waiter */
    else if (choice == 3)
    {
        pthread_mutex_lock(&forks[left]);
        pthread_mutex_lock(&forks[right]);

        printf("Waiter allowed P%d to eat\n", id);

        pthread_mutex_unlock(&forks[right]);
        pthread_mutex_unlock(&forks[left]);
    }

    /* Solution 4: Asymmetric */
    else if (choice == 4)
    {
        if (id == N - 1)
        {
            pthread_mutex_lock(&forks[right]);
            pthread_mutex_lock(&forks[left]);
        }
        else
        {
            pthread_mutex_lock(&forks[left]);
            pthread_mutex_lock(&forks[right]);
        }

        printf("P%d is eating\n", id);

        pthread_mutex_unlock(&forks[left]);
        pthread_mutex_unlock(&forks[right]);
    }

    return NULL;
}

int main()
{
    pthread_t p[N];
    int id[N];

    /* Initialize forks */
    for (int i = 0; i < N; i++)
    {
        pthread_mutex_init(&forks[i], NULL);
        id[i] = i;
    }

    /* Initialize semaphore */
    sem_init(&room, 0, N - 1);

    /* Keep showing menu until Exit */
    while (1)
    {
        printf("\n==============================\n");
        printf(" DINING PHILOSOPHERS PROBLEM\n");
        printf("==============================\n");

        printf("1. Semaphore\n");
        printf("2. Resource Ordering\n");
        printf("3. Waiter\n");
        printf("4. Asymmetric\n");
        printf("5. Exit\n");

        printf("\nEnter choice: ");
        scanf("%d", &choice);

        if (choice == 5)
        {
            printf("\nProgram exited.\n");
            break;
        }

        if (choice < 1 || choice > 5)
        {
            printf("\nInvalid choice!\n");
            continue;
        }

        printf("\nRunning solution %d...\n\n", choice);

        /* Create philosophers */
        for (int i = 0; i < N; i++)
        {
            pthread_create(&p[i],
                           NULL,
                           philosopher,
                           &id[i]);
        }

        /* Wait for all philosophers */
        for (int i = 0; i < N; i++)
        {
            pthread_join(p[i], NULL);
        }

        printf("\nSolution completed.\n");
    }

    return 0;
}
