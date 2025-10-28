#include <stdio.h>
//non premptive

struct Process {
    int id, Bt, Wt, TAt;
} P[20];

int main() {
    int i, n;

    printf("Enter the Number of Processes: ");
    scanf("%d", &n);

    for (i = 0; i < n; i++) {
        printf("\nEnter process id and burst time of P%d: ", i + 1);
        scanf("%d%d", &P[i].id, &P[i].Bt);
    }

    P[0].Wt = 0;
    P[0].TAt = P[0].Bt;

    for (i = 1; i < n; i++) {
        P[i].Wt = P[i - 1].TAt;
        P[i].TAt = P[i].Bt + P[i].Wt;
    }

    printf("PROCESS ID\tBURST TIME\tWAITING TIME\tTURNAROUND TIME\n");
    printf("------------------------------------------------------\n");

    for (i = 0; i < n; i++) {
        printf("%d\t\t%d\t\t%d\t\t%d\n", P[i].id, P[i].Bt, P[i].Wt, P[i].TAt);
    }

    return 0;
}
