#include <stdio.h>

// Function for Round Robin Scheduling
void find_round_robin(int n, int at[], int bt[], int tq, int wt[], int tat[]) {
    int rt[10], ct[10];
    int queue[100], front = 0, rear = 0;
    int visited[10] = {0};
    int completed = 0, current_time = 0;

    // Initialize remaining time array
    for (int i = 0; i < n; i++) {
        rt[i] = bt[i];
    }

    // Find the first arriving process to start the timeline
    int min_at = 9999, first_idx = 0;
    for (int i = 0; i < n; i++) {
        if (at[i] < min_at) {
            min_at = at[i];
            first_idx = i;
        }
    }
    
    current_time = min_at;
    queue[rear++] = first_idx;
    visited[first_idx] = 1;

    while (front < rear) {
        int idx = queue[front++];

        // Execute for time quantum or remaining time, whichever is smaller
        if (rt[idx] > tq) {
            current_time += tq;
            rt[idx] -= tq;
        } else {
            current_time += rt[idx];
            rt[idx] = 0;
            completed++;
            ct[idx] = current_time;
            tat[idx] = ct[idx] - at[idx];
            wt[idx] = tat[idx] - bt[idx];
        }

        // Push newly arrived processes into the queue
        for (int i = 0; i < n; i++) {
            if (at[i] <= current_time && rt[i] > 0 && !visited[i]) {
                queue[rear++] = i;
                visited[i] = 1;
            }
        }

        // If the current process is not finished, push it back to the queue
        if (rt[idx] > 0) {
            queue[rear++] = idx;
        }

        // If queue becomes empty but processes are still left, jump to the next arrival time
        if (front == rear && completed < n) {
            int next_idx = -1;
            int min_arrival = 9999;
            for (int i = 0; i < n; i++) {
                if (rt[i] > 0 && !visited[i]) {
                    if (at[i] < min_arrival) {
                        min_arrival = at[i];
                        next_idx = i;
                    }
                }
            }
            if (next_idx != -1) {
                if (at[next_idx] > current_time) {
                    current_time = at[next_idx];
                }
                queue[rear++] = next_idx;
                visited[next_idx] = 1;
            }
        }
    }
}

// Function to print results and averages
void print_results(int n, int at[], int bt[], int wt[], int tat[], char* title) {
    printf("\n--- %s ---\n", title);
    printf("PID\tArrival\tBurst\tWaiting\tTurnaround\n");
    
    float total_wt = 0, total_tat = 0;
    for (int i = 0; i < n; i++) {
        total_wt += wt[i];
        total_tat += tat[i];
        printf("%d\t%d\t%d\t%d\t%d\n", i + 1, at[i], bt[i], wt[i], tat[i]);
    }
    printf("Average Waiting Time: %.2f\n", total_wt / n);
    printf("Average Turnaround Time: %.2f\n", total_tat / n);
}

int main() {
    int n, tq, i;
    int at[10], bt[10];
    int wt[10], tat[10];

    printf("Enter number of processes (max 10): ");
    scanf("%d", &n);

    // Input Arrival Time and Burst Time
    for (i = 0; i < n; i++) {
        printf("\nProcess %d:\n", i + 1);
        printf("Arrival Time: ");
        scanf("%d", &at[i]);
        printf("Burst Time: ");
        scanf("%d", &bt[i]);
    }

    printf("Enter Time Quantum: ");
    scanf("%d", &tq);

    // Run Round Robin Scheduling
    find_round_robin(n, at, bt, tq, wt, tat);
    print_results(n, at, bt, wt, tat, "Round Robin Scheduling");

    return 0;
}
