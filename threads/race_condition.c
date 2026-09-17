#include<stdio.h> 

#include<pthread.h> 

 

long c=0; 

void *calc(void *args) 

{ 

for(int i=0;i<1000000;i++) 

c++; 

printf("Thread completed ID=%lu\n c=%ld\n",pthread_self(),c); 

return NULL; 

} 

int main() 

{ 

pthread_t p,q; 

pthread_create(&p,NULL,calc,NULL); 

pthread_create(&q,NULL,calc,NULL); 

pthread_join(p,NULL); 

pthread_join(q,NULL); 

printf("2 threads completed their work\n"); 

printf("Final value=%ld\n",c); 

return 0; 

} 
