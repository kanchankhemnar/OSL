#include <stdio.h>

#define MAX_PROCESSES 10

// Structure to represent a process
struct Process {
    int pid;          // Process ID
    int arrival_time; // Arrival time
    int burst_time;   // Burst time
    int remaining_time; // Remaining time for execution
    int completion_time; // Completion time
    int waiting_time; // Waiting time
    int turnaround_time; // Turnaround time
};

// Function to implement Shortest Job First (Preemptive)
void SJF_Preemptive(struct Process processes[], int n) {
    int time = 0; // Current time
    int completed = 0; // Counter to keep track of number of completed processes
    int min_index;
    int min_burst_time;
    float total_waiting_time = 0, total_turnaround_time = 0;

    // Initialize the remaining burst time for each process
    for (int i = 0; i < n; i++) {
        processes[i].remaining_time = processes[i].burst_time;
    }

    // Process scheduling loop
    while (completed < n) {
        min_burst_time = 9999;
        min_index = -1;

        // Find the process with the shortest remaining time
        for (int i = 0; i < n; i++) {
            if (processes[i].arrival_time <= time && processes[i].remaining_time > 0 && processes[i].remaining_time < min_burst_time) {
                min_burst_time = processes[i].remaining_time;
                min_index = i;
            }
        }

        if (min_index == -1) {
            time++;
            continue;
        }

        // Decrement the remaining time of the selected process
        processes[min_index].remaining_time--;
        time++;

        // If a process finishes, calculate its completion, waiting, and turnaround time
        if (processes[min_index].remaining_time == 0) {
            processes[min_index].completion_time = time;
            processes[min_index].turnaround_time = processes[min_index].completion_time - processes[min_index].arrival_time;
            processes[min_index].waiting_time = processes[min_index].turnaround_time - processes[min_index].burst_time;

            total_waiting_time += processes[min_index].waiting_time;
            total_turnaround_time += processes[min_index].turnaround_time;

            completed++;
        }
    }

    // Output the results
    printf("\nPID\tArrival Time\tBurst Time\tCompletion Time\tWaiting Time\tTurnaround Time\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n", processes[i].pid, processes[i].arrival_time, processes[i].burst_time,
               processes[i].completion_time, processes[i].waiting_time, processes[i].turnaround_time);
    }

    // Output average times
    printf("\nAverage Waiting Time: %.2f\n", total_waiting_time / n);
    printf("Average Turnaround Time: %.2f\n", total_turnaround_time / n);
}

int main() {
    int n;

    // Accept the number of processes
    printf("Enter number of processes: ");
    scanf("%d", &n);

    struct Process processes[MAX_PROCESSES];

    // Accept process details: PID, arrival time, and burst time
    for (int i = 0; i < n; i++) {
        processes[i].pid = i + 1;
        printf("Enter arrival time and burst time for process %d: ", i + 1);
        scanf("%d %d", &processes[i].arrival_time, &processes[i].burst_time);
    }

    // Call SJF Preemptive function
    SJF_Preemptive(processes, n);

    return 0;
}
