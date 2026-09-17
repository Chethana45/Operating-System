void find_non_preemptive(int n, int at[], int bt[], int wt[], int tat[]) {
    int is_completed[10] = {0};
    int completed = 0, current_time = 0;
    int ct[10];

    while (completed < n) {
        int idx = -1;
        int min_val = 9999;

        for (int i = 0; i < n; i++) {
            if (at[i] <= current_time && !is_completed[i]) {
                if (bt[i] < min_val) {
                    min_val = bt[i];
                    idx = i;
                }
            }
        }

        if (idx == -1) {
            current_time++; // CPU is idle
        } else {
            current_time += bt[idx];
            ct[idx] = current_time;
            tat[idx] = ct[idx] - at[idx];
            wt[idx] = tat[idx] - bt[idx];
            is_completed[idx] = 1;
            completed++;
        }
    }
}

