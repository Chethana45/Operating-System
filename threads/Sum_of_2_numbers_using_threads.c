

 

#include<stdio.h> 

#include<pthread.h> 

 

void *sum(void *args) 

{ 

int *a= (int *)args; 

printf("Sum=%d\n",a[0]+a[1]); 

return NULL; 

} 

 

int main() 

{ 

int a[2]; 

pthread_t t; 

printf("Enter 2 numbers:\n"); 

scanf("%d%d",&a[0],&a[1]); 

 

pthread_create(&t,NULL,sum,a); 

pthread_join(t,NULL); 

return 0; 

} 
