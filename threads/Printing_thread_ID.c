

 

#include<stdio.h> 

#include<pthread.h> 

 

void *disp(void *args) 

{ 

printf("Hello, Ruvanthika\n"); 

printf("Current thread ID=%lu\n",pthread_self()); 

return NULL; 

} 

 

int main() 

{ 

pthread_t t; 

pthread_create(&t,NULL,disp,NULL); 

pthread_join(t,NULL); 

printf("Thread completed its work\n"); 

printf("Current thread ID=%lu\n",pthread_self()); 

return 0; 

} 
