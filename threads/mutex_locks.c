#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
long c=0;
pthread_mutex_t l=PTHREAD_MUTEX_INITIALIZER;
void *calc(void *args)
{
        pthread_mutex_lock(&l);
        for(int i=0;i<10;i++){
                c++;

        pthread_mutex_unlock(&l);}
        printf("c is  c=%ld\n",c);
        printf("
        return NULL;
}
int main(){
        pthread_t p,q;
        pthread_create(&p,NULL,calc,NULL);
        pthread_create(&q,NULL,calc,NULL);
        pthread_join(p,NULL);
        pthread_join(q,NULL);
        printf("Both threads completed their work\n");
        printf("Final value=%ld",c);
        pthread_mutex_destroy(&l);
        return 0;

}
