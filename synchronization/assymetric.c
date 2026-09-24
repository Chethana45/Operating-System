#include <stdio.h>
#include <pthread.h>

#define N 5

pthread_mutex_t fork[N];

void *philosopher(void *arg)
{
    int id = *(int *)arg;

    int left = id;
    int right = (id + 1) % N;

    if(id == N - 1)
    {
        pthread_mutex_lock(&fork[right]);
        pthread_mutex_lock(&fork[left]);
    }
    else
    {
        pthread_mutex_lock(&fork[left]);
        pthread_mutex_lock(&fork[right]);
    }

    printf("P%d is eating\n", id);

    pthread_mutex_unlock(&fork[left]);
    pthread_mutex_unlock(&fork[right]);

    return NULL;
}

int main()
{
    pthread_t p[N];
    int id[N];

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
