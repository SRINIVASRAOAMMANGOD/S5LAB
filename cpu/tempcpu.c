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

void fcfs(struct process processes[], int n) {
    int current_time = 0;
    for (int i = 0; i < n; i++) {
        if (current_time < processes[i].arrival) {
            current_time = processes[i].arrival;
        }
        processes[i].waiting = current_time - processes[i].arrival;
        processes[i].turnaround = processes[i].waiting + processes[i].burst;
        current_time += processes[i].burst;
    }
}

void sjf(struct process processes[], int n) {
    int current_time = 0, completed = 0;

    while (completed < n) {
        int shortest = -1, min_burst = INT_MAX;

        for (int i = 0; i < n; i++) {
            if (processes[i].arrival <= current_time && processes[i].remaining > 0 &&
                processes[i].burst < min_burst) {
                shortest = i;
                min_burst = processes[i].burst;
            }
        }

        if (shortest == -1) {
            current_time++;
            continue;
        }

        processes[shortest].waiting = current_time - processes[shortest].arrival;
        processes[shortest].turnaround = processes[shortest].waiting + processes[shortest].burst;
        current_time += processes[shortest].burst;
        processes[shortest].remaining = 0;
        completed++;
    }
}

void roundRobin(struct process processes[], int n, int quantum) {
    int current_time = 0, completed = 0;

    while (completed < n) {
        for (int i = 0; i < n; i++) {
            if (processes[i].remaining > 0) {
                int time_slice = (processes[i].remaining > quantum) ? quantum : processes[i].remaining;
                processes[i].remaining -= time_slice;
                current_time += time_slice;

                if (processes[i].remaining == 0) {
                    processes[i].waiting = current_time - processes[i].arrival - processes[i].burst;
                    processes[i].turnaround = processes[i].waiting + processes[i].burst;
                    completed++;
                }
            }
        }
    }
}

void priority(struct process processes[], int n) {
    int current_time = 0, completed = 0;

    while (completed < n) {
        int highest_priority = -1, min_priority = INT_MAX;

        for (int i = 0; i < n; i++) {
            if (processes[i].arrival <= current_time && processes[i].remaining > 0 &&
                processes[i].priority < min_priority) {
                highest_priority = i;
                min_priority = processes[i].priority;
            }
        }

        if (highest_priority == -1) {
            current_time++;
            continue;
        }

        processes[highest_priority].waiting = current_time - processes[highest_priority].arrival;
        processes[highest_priority].turnaround =
            processes[highest_priority].waiting + processes[highest_priority].burst;

        current_time += processes[highest_priority].burst;
        processes[highest_priority].remaining = 0;
        completed++;
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
    int n, quantum, choice;

    do {
        printf("\nSelect the scheduling algorithm\n");
        printf("1. FCFS\n2. SJF (Non-preemptive)\n3. Round Robin\n4. Priority (Non-preemptive)\n5. Exit\n");

        printf("Enter the choice: ");
        scanf("%d", &choice);

        if (choice == 5) {
            printf("Exiting...\n");
            break;
        }

        printf("Enter the number of processes: ");
        scanf("%d", &n);

        for (int i = 0; i < n; i++) {
            printf("P%d:\nArrival Time: ", i + 1);
            scanf("%d", &processes[i].arrival);
            printf("Burst Time: ");
            scanf("%d", &processes[i].burst);

            if (choice == 4) {
                printf("Priority: ");
                scanf("%d", &processes[i].priority);
            } else {
                processes[i].priority = 0;
            }

            processes[i].pid = i + 1;
            processes[i].remaining = processes[i].burst;
        }

        if (choice == 3) {
            printf("\nEnter the time quantum: ");
            scanf("%d", &quantum);
        }

        switch (choice) {
            case 1:
                printf("\nFCFS Scheduling\n");
                fcfs(processes, n);
                break;

            case 2:
                printf("\nSJF (Non-preemptive) Scheduling\n");
                sjf(processes, n);
                break;

            case 3:
                printf("\nRound Robin Scheduling\n");
                roundRobin(processes, n, quantum);
                break;

            case 4:
                printf("\nPriority (Non-preemptive) Scheduling\n");
                priority(processes, n);
                break;

            default:
                printf("Invalid choice..\n");
                continue;
        }

        display(processes, n);

    } while (choice != 5);

    return 0;
}
