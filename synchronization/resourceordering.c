#include <stdio.h>
#include <pthread.h>

#define N 5

pthread_mutex_t fork[N];

void *philosopher(void *arg)
{
    int id = *(int *)arg;

    int left = id;
    int right = (id + 1) % N;

    int first = left < right ? left : right;
    int second = left < right ? right : left;

    pthread_mutex_lock(&fork[first]);
    printf("P%d picked fork %d\n", id, first);

    pthread_mutex_lock(&fork[second]);
    printf("P%d picked fork %d\n", id, second);

    printf("P%d is eating\n", id);

    pthread_mutex_unlock(&fork[second]);
    pthread_mutex_unlock(&fork[first]);

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
