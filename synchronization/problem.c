#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

#define N 5

pthread_mutex_t forks[N];

void *philosopher(void *arg)
{
    int id = *(int *)arg;

    int left = id;
    int right = (id + 1) % N;

    printf("P%d is thinking\n", id);

    /* Pick left fork */
    pthread_mutex_lock(&forks[left]);
    printf("P%d picked left fork %d\n", id, left);

    sleep(1);

    /* Pick right fork */
    pthread_mutex_lock(&forks[right]);
    printf("P%d picked right fork %d\n", id, right);

    printf("P%d is eating\n", id);

    pthread_mutex_unlock(&forks[right]);
    pthread_mutex_unlock(&forks[left]);

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

    /* Create philosophers */
    for (int i = 0; i < N; i++)
    {
        pthread_create(&p[i],
                       NULL,
                       philosopher,
                       &id[i]);
    }

    /* Wait for philosophers */
    for (int i = 0; i < N; i++)
    {
        pthread_join(p[i], NULL);
    }

    return 0;
}
