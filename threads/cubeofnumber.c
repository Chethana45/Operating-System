

#include<stdio.h> 

#include<stdlib.h> 

#include<pthread.h> 

 

void *calc(void *args) 

{ 

int *a= (int *)args; 

int *r=malloc(sizeof(int)); 

*r=(*a)*(*a)*(*a); 

return r; 

 

} 

int main() 

{ 

int a; 

printf("Enter number:\n"); 

scanf("%d",&a); 

void *r; 

pthread_t t; 

pthread_create(&t,NULL,calc,&a); 

pthread_join(t,&r); 

printf("Cube=%d\n",*(int *)r); 

free(r); 

return 0; 

} 
