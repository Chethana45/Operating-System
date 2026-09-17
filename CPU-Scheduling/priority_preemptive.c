// 2. Function for Preemptive Priority Scheduling
void find_priority_preemptive(int n, int at[], int bt[], int pr[], int wt[], int tat[]) {
    int rt[10];
    for (int i = 0; i < n; i++) {
        rt[i] = bt[i]; // Remaining time array
    }

    int completed = 0, current_time = 0;
    int ct[10];

    while (completed < n) {
        int idx = -1;
        int highest_priority = 9999; // Lower number means higher priority

        for (int i = 0; i < n; i++) {
            if (at[i] <= current_time && rt[i] > 0) {
                if (pr[i] < highest_priority) {
                    highest_priority = pr[i];
                    idx = i;
                }
            }
        }

        if (idx == -1) {
            current_time++;
            continue;
        }

        rt[idx]--; // Run for 1 unit of time
        current_time++;

        if (rt[idx] == 0) {
            completed++;
            ct[idx] = current_time;
            tat[idx] = ct[idx] - at[idx];
            wt[idx] = tat[idx] - bt[idx];
        }
    }
}

