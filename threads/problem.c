#include <pthread.h>
int c=0;
void *counter1(void* args){
        for(int i=1;i<10;i++){
                c++;

        }
        printf("the count is :%d\n",c);
                return NULL;
        }

void *counter2(void* args){
        for(int i=1;i<10;i++){
                c++;}
                printf("the count is :%d\n",c);


return NULL;
}
int main(){
        pthread_t t1,t2;
pthread_create(&t1,NULL,counter1,NULL);
pthread_create(&t2,NULL,counter2,NULL);
        pthread_join(t1,NULL);
        pthread_join(t2,NULL);
        return 0;
}

