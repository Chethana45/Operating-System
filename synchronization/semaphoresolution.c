#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>

#define N 5

pthread_mutex_t fork[N];
sem_t room;

void *philosopher(void *arg)
{
    int id = *(int *)arg;
    int left = id;
    int right = (id + 1) % N;

    sem_wait(&room);

    pthread_mutex_lock(&fork[left]);
    printf("P%d picked fork %d\n", id, left);

    pthread_mutex_lock(&fork[right]);
    printf("P%d picked fork %d\n", id, right);

    printf("P%d is eating\n", id);

    pthread_mutex_unlock(&fork[right]);
    pthread_mutex_unlock(&fork[left]);

    sem_post(&room);

    return NULL;
}

int main()
{
    pthread_t p[N];
    int id[N];

    sem_init(&room, 0, N - 1);

    for(int i = 0; i < N; i++)
        pthread_mutex_init(&fork[i], NULL);

    for(int i = 0; i < N; i++)
    {
        id[i] = i;
        pthread_create(&p[i], NULL, philosopher, &id[i]);
    }

    for(int i = 0; i < N; i++)
        pthread_join(p[i], NULL);

    return 0;
}
