#include <stdio.h>
#include <pthread.h>

#define N 5

pthread_mutex_t mutex;
int fork[N] = {1,1,1,1,1};

void *philosopher(void *arg)
{
    int id = *(int *)arg;

    int left = id;
    int right = (id + 1) % N;

    pthread_mutex_lock(&mutex);

    if(fork[left] && fork[right])
    {
        fork[left] = 0;
        fork[right] = 0;

        printf("P%d got forks %d and %d\n",
               id, left, right);

        printf("P%d is eating\n", id);

        fork[left] = 1;
        fork[right] = 1;
    }
    else
    {
        printf("P%d must wait\n", id);
    }

    pthread_mutex_unlock(&mutex);

    return NULL;
}

int main()
{
    pthread_t p[N];
    int id[N];

    pthread_mutex_init(&mutex, NULL);

    for(int i = 0; i < N; i++)
    {
        id[i] = i;
        pthread_create(&p[i], NULL, philosopher, &id[i]);
    }

    for(int i = 0; i < N; i++)
        pthread_join(p[i], NULL);

    return 0;
}
