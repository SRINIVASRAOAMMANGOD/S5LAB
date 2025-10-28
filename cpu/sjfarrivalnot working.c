#include <stdio.h>
//working for both arrival and non arrival resepctive code
//not working
struct Process {
    int id, Bt, at, Wt, TAt;
} P[20], temp;
//nonpre
int main() {
    int i, j, n,twt=0,ttat=0;

    printf("Enter the Number of Processes: ");
    scanf("%d", &n);

    // Input: id, burst time, arrival time
    for (i = 0; i < n; i++) {
        printf("\nEnter process id, burst time and arrival time of P-%d: ", i + 1);
        scanf("%d%d%d", &P[i].id, &P[i].Bt, &P[i].at);
    }

    // Step 1: Sort by Arrival Time
    for (i = 0; i < n - 1; i++) {
        for (j = 0; j < n - i - 1; j++) {
            if (P[j].at > P[j + 1].at) {
                temp = P[j];
                P[j] = P[j + 1];
                P[j + 1] = temp;
            }
        }
    }

    // Step 2: For equal arrival times, sort by Burst Time
    for (i = 0; i < n - 1; i++) {
        for (j = 0; j < n - i - 1; j++) {
            if (P[j].at == P[j + 1].at && P[j].Bt > P[j + 1].Bt) {
                temp = P[j];
                P[j] = P[j + 1];
                P[j + 1] = temp;
            }
        }
    }

    int current_time = 0;
    for (i = 0; i < n; i++) {
        if (P[i].at > current_time)
            current_time = P[i].at;

        P[i].Wt = current_time - P[i].at;
        twt+= P[i].Wt;
        P[i].TAt = P[i].Wt + P[i].Bt;
        ttat+= P[i].TAt;
        current_time += P[i].Bt;
    }
    for (i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (P[j].id > P[j + 1].id) {
                
                temp = P[j];
                P[j] = P[j + 1];
                P[j + 1] = temp;
            }
        }
    }

    // Output Table
    printf("\nPROCESS ID\tBURST TIME\tARRIVAL TIME\tWAITING TIME\tTURNAROUND TIME\n");
    printf("----------------------------------------------------------------------\n");
    for (i = 0; i < n; i++) {
        printf("%d\t\t%d\t\t%d\t\t%d\t\t%d\n", P[i].id, P[i].Bt, P[i].at, P[i].Wt, P[i].TAt);
    }
    printf("AVERAGE WAITING %.2f AVERAGE TURNAROUND %.2f",(float)twt/n,(float)ttat/n);

    return 0;
}
