DATA SEGMENT
N1 DW 1731H
N2 DW 9212H
N3 DW ?
DATA ENDS

CODE SEGMENT
ASSUME CS:CODE, DS:DATA

START:
    MOV AX, DATA
    MOV DS, AX
    XOR AX, AX
    MOV BX, AX
    MOV AX, N1
    ADD AX, N2
    MOV N3, AX
    JNC STOP
    INC BX

STOP:
    MOV CX, AX
    MOV AH, 4CH
    INT 21H

CODE ENDS
END START
mount c c:\dos\asm
c:
edit program.asm

masm program.asm      ; Assembles to program.obj
link program.obj     ; Links to program.exe
program.exe
debug program.exe

u	Disassemble code (e.g., u 100 shows instructions)
r	Show registers
d	Dump memory (e.g., d 0 or d ds:0)
t	Trace one instruction at a time
g	Run the program
q	Quit DEBUG
p (Proceed)	Executes the entire procedure call as one step, then pauses at the next instruction


#include <stdio.h>

int main() {
    int n, i, at[100], bt[100], rt[100], ts, time = 0, remain = 0, flag = 0;
    int total_wt = 0, total_tat = 0;
    
    printf("Enter the number of processes: ");
    scanf("%d", &n);
    remain = n;  // Remaining processes
    
    for (i = 0; i < n; i++) {
        printf("Enter arrival time and burst time for process P%d: ", i + 1);
        scanf("%d %d", &at[i], &bt[i]);
        rt[i] = bt[i];  // Copy burst time to remaining time
    }

    printf("Enter time slice: ");
    scanf("%d", &ts);

    int completed = 0;  // Tracks completed processes
    int wt[100] = {0}, tat[100] = {0};  // Arrays to store waiting time & turnaround time

    while (completed < n) {
        flag = 0;  // Reset flag for each cycle

        for (i = 0; i < n; i++) {
            if (rt[i] > 0 && at[i] <= time) {  // Process must have arrived & have remaining time
                flag = 1;  // At least one process is being executed
                
                if (rt[i] <= ts) {
                    time += rt[i];  // Process finishes execution
                    rt[i] = 0;
                    completed++;

                    tat[i] = time - at[i];  // Turnaround time
                    wt[i] = tat[i] - bt[i];  // Waiting time

                    total_wt += wt[i];
                    total_tat += tat[i];
                } else {
                    rt[i] -= ts;  // Reduce remaining time
                    time += ts;  // Increase the current time
                }
            }
        }

        // If no process is available at the current time, increment time
        if (flag == 0) {
            time++;
        }
    }

    // Display results
    printf("\nProcess\tAT\tBT\tWT\tTAT\n");
    for (i = 0; i < n; i++) {
        printf("P%d\t%d\t%d\t%d\t%d\n", i + 1, at[i], bt[i], wt[i], tat[i]);
    }

    printf("\nTotal Waiting Time: %d", total_wt);
    printf("\nTotal Turnaround Time: %d", total_tat);
    printf("\nAverage Waiting Time: %.2f", (float)total_wt / n);
    printf("\nAverage Turnaround Time: %.2f\n", (float)total_tat / n);

    return 0;
}