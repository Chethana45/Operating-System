#include <stdio.h>

void waiting(int processes[],int n, int bt[],int wt[]){
        wt[0]=0;
        for(int i=1;i<n;i++){
                wt[i]=bt[i-1]+wt[i-1];
        }
}
void turnaroundtime(int processes[],int n,int bt[],int wt[],int tat[]){
        for(int i=0;i<n;i++){
                tat[i]=wt[i]+bt[i];
        }}
void avgtime(int processes[],int n,int bt[]){
        int wt[n],tat[n],total_wt=0,total_tat=0;

        waiting(processes,n,bt,wt);
        turnaroundtime(processes,n,bt,wt,tat);
        printf("%-10s %-10s %-12s %-18s\n",
       "Process", "Burst Time", "Waiting Time", "Turn Around Time");
        for(int i=0;i<n;i++){
                total_wt= total_wt+wt[i];
                total_tat= total_tat+tat[i];

                                                                  printf("%-10d %-12d %-15d %-18d\n",
           processes[i], bt[i], wt[i], tat[i]);
        }
        float s=(float)total_wt/(float)n;
        float t=(float)total_tat/(float)n;
        printf("Average Waiting Time =%.2f\n",s);
        printf("\n");
        printf("Average turn around time =%.2f\n",t);
}
int main(){
        int processes[]={1,2,3};
        int n= sizeof processes/ sizeof processes[0];
        int bt[]={10,5,8};
        avgtime(processes,n,bt);
                                   return 0;
}
