// #include <stdio.h>

// struct Process {
//     int id, Bt, Pr, Wt, TAt;
// } P[20], temp;

// int main() {
//     int i, j, n;

//     printf("Enter the Number of Processes: ");
//     scanf("%d", &n);

//     for (i = 0; i < n; i++) {
//         printf("\nEnter process id, burst time and priority of P-%d: ", i + 1);
//         scanf("%d%d%d", &P[i].id, &P[i].Bt, &P[i].Pr);
//     }

//     // Sorting processes based on priority (Higher priority first - lower value means higher priority)
//     for (i = 0; i < n - 1; i++) {
//         for (j = 0; j < n - i - 1; j++) {
//             if (P[j].Pr > P[j + 1].Pr) {
//                 temp = P[j];
//                 P[j] = P[j + 1];
//                 P[j + 1] = temp;
//             }
//         }
//     }

//     P[0].Wt = 0;
//     P[0].TAt = P[0].Bt;

//     for (i = 1; i < n; i++) {
//         P[i].Wt = P[i - 1].TAt;
//         P[i].TAt = P[i].Bt + P[i].Wt;
//     }

//     printf("PROCESS ID\tBURST TIME\tPRIORITY\tWAITING TIME\tTURNAROUND TIME\n");
//     printf("---------------------------------------------------------------\n");

//     for (i = 0; i < n; i++) {
//         printf("%d\t\t%d\t\t%d\t\t%d\t\t%d\n", P[i].id, P[i].Bt, P[i].Pr, P[i].Wt, P[i].TAt);
//     }

//     return 0;
// }
//tested working
//2nd test working
#include <stdio.h>
//nonpre
struct Process {
    int id, bt, at, pr, wt, tat;
};

int main() {
    int n, i, j;
    struct Process p[20], temp;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    for (i = 0; i < n; i++) {
        printf("Enter process id, burst time, arrival time, and priority (lower = higher): ");
        scanf("%d%d%d%d", &p[i].id, &p[i].bt, &p[i].at, &p[i].pr);
    }

    // Sort by arrival time first, then priority
    for (i = 0; i < n-1; i++) {
        for (j = 0; j < n-i-1; j++) {
            if (p[j].at > p[j+1].at || 
               (p[j].at == p[j+1].at && p[j].pr > p[j+1].pr)) {
                temp = p[j];
                p[j] = p[j+1];
                p[j+1] = temp;
            }
        }
    }

    int time = 0;
    for (i = 0; i < n; i++) {
        if (time < p[i].at)
            time = p[i].at;

        p[i].wt = time - p[i].at;
        p[i].tat = p[i].wt + p[i].bt;
        time += p[i].bt;
    }
    for (i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (p[j].id > p[j + 1].id) {
                
                temp = p[j];
                p[j] = p[j + 1];
                p[j + 1] = temp;
            }
        }
    }
    printf("\nID\tBT\tAT\tPR\tWT\tTAT\n");
    for (i = 0; i < n; i++) {
        printf("%d\t%d\t%d\t%d\t%d\t%d\n", p[i].id, p[i].bt, p[i].at, p[i].pr, p[i].wt, p[i].tat);
    }

    return 0;
}
