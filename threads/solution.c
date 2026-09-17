#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
int count=0;
int flag[2]={0,0};
int turn;
void enter_region(int process){
int other=1-process;
flag[process]=1;
turn=other;
while(flag[other]&&turn==other);
}
void leave_region(int process){
        flag[process]=0;}
        void *process0(void* arg){
                for(int i=0;i<5;i++){
                        enter_region(0);
                        count++;

                sleep(1);
                leave_region(0);
                printf("process0 is in reminder section\n");
                sleep(1);
                }
                  printf("process 0 entered critical section. count=%d\n",count);

                return NULL;}
                void *process1(void *arg){
                        for(int i=0;i<5;i++){
                                enter_region(1);
                                count++;

                                sleep(1);
                                leave_region(1);
                                printf("process1 is in reminder section\n");
                                sleep(1);
                }printf("process1 entered critical section. count = %d\n",count);
           return NULL;
                }


 int main(){
         pthread_t t0,t1;
         pthread_create(&t0,NULL,process0,NULL);
         pthread_create(&t1,NULL,process1,NULL);
         pthread_join(t0,NULL);
         pthread_join(t1,NULL);
         printf("\nfinal count= %d\n",count);


 return 0;}
                 

