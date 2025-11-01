#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

struct process {
    int pid;
    int arrival;
    int burst;
    int priority;
    int remaining;
    int waiting;
    int turnaround;
}processes[100];

void roundRobin(struct process processes[], int n, int quantum) {
    int current_time = 0, completed = 0;
    
    // Initialize remaining time for all processes
    for(int i = 0; i < n; i++) {
        processes[i].remaining = processes[i].burst;
    }

    while (completed < n) {
        int flag = 0;  // To check if any process is eligible at current time
        
        for (int i = 0; i < n; i++) {
            // Process only if it has arrived and has remaining time
            if (processes[i].arrival <= current_time && processes[i].remaining > 0) {
                flag = 1;  // Found an eligible process
                
                // Calculate time slice for this round
                int time_slice = (processes[i].remaining > quantum) ? quantum : processes[i].remaining;
                processes[i].remaining -= time_slice;
                current_time += time_slice;

                if (processes[i].remaining == 0) {
                    completed++;
                    // Calculate waiting and turnaround time when process completes
                    processes[i].turnaround = current_time - processes[i].arrival;
                    processes[i].waiting = processes[i].turnaround - processes[i].burst;
                }
            }
        }
        
        // If no process was eligible, increment time
        if (flag == 0) {
            current_time++;
        }
    }
}

void display(struct process processes[], int n) {
    int total_waiting = 0, total_turnaround = 0;

    printf("\nPID\tArrival\tBurst\tPriority\tWaiting\tTurnaround\n");

    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t%d\t%d\t\t%d\t%d\n", processes[i].pid, processes[i].arrival,
               processes[i].burst, processes[i].priority,
               processes[i].waiting, processes[i].turnaround);

        total_waiting += processes[i].waiting;
        total_turnaround += processes[i].turnaround;
    }

    float avg_waiting = (float)total_waiting / n;
    float avg_turnaround = (float)total_turnaround / n;

    printf("\nTotal Waiting Time: %d", total_waiting);
    printf("\nTotal Turnaround Time: %d", total_turnaround);
    printf("\nAverage Waiting Time: %.2f", avg_waiting);
    printf("\nAverage Turnaround Time: %.2f\n", avg_turnaround);
}
int main() {
    int n, quantum;

    printf("Enter the number of processes: ");
    scanf("%d", &n);

    // Input process details
    for (int i = 0; i < n; i++) {
        printf("P%d:\nArrival Time: ", i + 1);
        scanf("%d", &processes[i].arrival);
        printf("Burst Time: ");
        scanf("%d", &processes[i].burst);
        processes[i].pid = i + 1;
    }

    // Input time quantum
    printf("\nEnter the time quantum: ");
    scanf("%d", &quantum);

    // Execute Round Robin scheduling
    printf("\nRound Robin Scheduling with Arrival Time\n");
    roundRobin(processes, n, quantum);

    // Display results
    display(processes, n);

    return 0;
}
    