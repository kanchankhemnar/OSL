#include <stdio.h>

#define MAX 10

typedef struct {
    int pid;
    int at;      // Arrival Time
    int bt;      // Burst Time
    int remaining_bt;
    int wt;
    int tat;
} Process;

void round_robin(Process processes[], int n, int q) {
    int time = 0, completed = 0;

    while (completed < n) {
        int all_idle = 1;

        for (int i = 0; i < n; i++) {
            if (processes[i].remaining_bt > 0 && processes[i].at <= time) {
                all_idle = 0;
                if (processes[i].remaining_bt > q) {
                    time += q;
                    processes[i].remaining_bt -= q;
                } else {  // Process can complete within quantum
                    time += processes[i].remaining_bt;
                    processes[i].tat = time - processes[i].at;
                    processes[i].wt = processes[i].tat - processes[i].bt;
                    processes[i].remaining_bt = 0;
                    completed++;
                }
            }
        }

        if (all_idle) time++;
    }

    // Display results
    printf("\nPID\tAT\tBT\tWT\tTAT\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t%d\t%d\t%d\n", processes[i].pid, processes[i].at, processes[i].bt, processes[i].wt, processes[i].tat);
    }
}

int main() {
    int n, q;
    Process processes[MAX];

    printf("Enter number of processes: ");
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        processes[i].pid = i + 1;
        printf("Enter Arrival Time and Burst Time for Process %d: ", i + 1);
        scanf("%d %d", &processes[i].at, &processes[i].bt);
        processes[i].remaining_bt = processes[i].bt;
    }

    printf("Enter Time Quantum: ");
    scanf("%d", &q);

    round_robin(processes, n, q);

    return 0;
}
