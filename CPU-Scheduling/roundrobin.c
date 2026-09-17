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
