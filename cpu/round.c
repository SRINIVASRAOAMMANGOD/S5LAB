#include <stdio.h>
//pre
struct Process {
    int id, Bt, tBt, Wt, TAt;
} P[20];

int main() {
    int i, n, tq;
    int x, y;

    printf("Enter the Number of Processes: ");
    scanf("%d", &n);

    for (i = 0; i < n; i++) {
        printf("\nEnter process id and burst time of P-%d: ", i + 1);
        scanf("%d%d", &P[i].id, &P[i].Bt);
        P[i].tBt = P[i].Bt;
    }

    printf("Enter the time quantum: ");
    scanf("%d", &tq);

    x = 0; // 0th time
    y = 0; // 0 processes completed
    i = 0; // ith process
    //not working
    
    while (1) {
        if (P[i].Bt > 0) {
            if (P[i].Bt > tq) {
                P[i].Bt = P[i].Bt - tq;
                x = x + tq;
            } else {
                x = x + P[i].Bt;
                P[i].Bt = 0;
                P[i].TAt = x;
                P[i].Wt = P[i].TAt - P[i].tBt;
                y++;
                if (y == n)
                    break;
            }
        }

        if (i == n - 1)
            i = 0;
        else
            i = i + 1;
    }

    printf("PROCESS ID\tBURST TIME\tWAITING TIME\tTURNAROUND TIME\n");
    printf("------------------------------------------------------\n");
    
    for (i = 0; i < n; i++) {
        printf("%d\t\t%d\t\t%d\t\t%d\n", P[i].id, P[i].tBt, P[i].Wt, P[i].TAt);
    }

    return 0;
}
