 

#include<stdio.h> 

#include<pthread.h> 

long c=0; 

pthread_mutex_t l=PTHREAD_MUTEX_INITIALIZER; 

void *calc(void *args) 

{ 

pthread_mutex_lock(&l); 

for(int i=0;i<1000000;i++) 

c++; 

printf("Thread completed ID:%lu \n c=%ld\n",pthread_self(),c); 

pthread_mutex_unlock(&l); 

return NULL; 

} 

int main() 

{ 

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
