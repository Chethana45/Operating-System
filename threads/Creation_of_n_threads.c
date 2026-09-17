

 

#include<stdio.h> 

#include<pthread.h> 

 

void *disp(void *args) 

{ 

int *a= (int *)args; 

printf("Thread %d : %lu\n",*a,pthread_self());	 

return NULL; 

} 

 

int main() 

{ 

int n; 

printf("Enter no.of threads:\n"); 

scanf("%d",&n); 

pthread_t t[n]; 

 

for(int i=0;i<n;i++) 

pthread_create(&t[i],NULL,disp,&i); 

 

for(int i=0;i<n;i++) 

pthread_join(t[i],NULL); 

 

return 0; 

} 
