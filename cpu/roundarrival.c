#include <stdio.h>
//pre
//tested 2nd
struct Process {
    int id, Bt, tBt, Wt, TAt, arrivalTime;
} P[20];

int main() {
    int i, n, tq;
    int x = 0, y = 0; // x: current time, y: processes completed
    int flag;
    float totalWT = 0, totalTAT = 0;

    printf("Enter the Number of Processes: ");
    scanf("%d", &n);

    for (i = 0; i < n; i++) {
        printf("\nEnter process id, arrival time and burst time of P-%d: ", i + 1);
        scanf("%d%d%d", &P[i].id, &P[i].arrivalTime, &P[i].Bt);
        P[i].tBt = P[i].Bt;
    }

    printf("Enter the time quantum: ");
    scanf("%d", &tq);

    while (y < n) {
        flag = 0;

        for (i = 0; i < n; i++) {
            if (P[i].Bt > 0 && P[i].arrivalTime <= x) {
                flag = 1;
                if (P[i].Bt > tq) {
                    x += tq;
                    P[i].Bt -= tq;
                } else {
                    x += P[i].Bt;
                    P[i].Bt = 0;
                    P[i].TAt = x - P[i].arrivalTime;
                    P[i].Wt = P[i].TAt - P[i].tBt;
                    totalWT += P[i].Wt;
                    totalTAT += P[i].TAt;
                    y++;
                }
            }
        }
        // If no process was ready to execute, increase time
        if (flag == 0)
            x++;
    }

    printf("\nPROCESS ID\tARRIVAL TIME\tBURST TIME\tWAITING TIME\tTURNAROUND TIME\n");
    printf("-------------------------------------------------------------------------\n");

    for (i = 0; i < n; i++) {
        printf("%d\t\t%d\t\t%d\t\t%d\t\t%d\n",
               P[i].id, P[i].arrivalTime, P[i].tBt, P[i].Wt, P[i].TAt);
    }

    printf("\nAverage Waiting Time: %.2f", totalWT / n);
    printf("\nAverage Turnaround Time: %.2f\n", totalTAT / n);

    return 0;
}
