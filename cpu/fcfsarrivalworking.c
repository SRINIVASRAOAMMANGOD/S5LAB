#include <stdio.h>
//non pre
struct Process {
    int id, Bt, Wt, CT,at,Tat,Temp;
} P[20],temp;

int main() {
    int i, n;

    printf("Enter the Number of Processes: ");
    scanf("%d", &n);

    for (i = 0; i < n; i++) {
        printf("\nEnter process id and burst time and arrival time of P%d: ", i + 1);
        scanf("%d%d%d", &P[i].id, &P[i].Bt,&P[i].at);
    }
    //sorting based on arrival
    for (i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (P[j].at > P[j + 1].at) {
                
                temp = P[j];
                P[j] = P[j + 1];
                P[j + 1] = temp;
            }
        }
    }
    //tat=ct-at
    //wt=tat-bt
    //P[0].Wt = 0;
    P[0].CT = P[0].at + P[0].Bt;
    P[0].Tat = P[0].CT-P[0].at;
    P[0].Wt = P[0].Tat-P[0].Bt;

    // for (i = 1; i < n; i++) {
    //     P[i].Temp = P[i - 1].CT;
    //     P[i].CT = P[i].Bt + P[i].Temp;
    //     P[i].Tat = P[i].CT-P[i].at;
    //     P[i].Wt = P[i].Tat-P[i].Bt;
    // }
    for (i = 1; i < n; i++) {
                if (P[i - 1].CT < P[i].at)
                    P[i].Temp = P[i].at; // idle 
                else  
                    P[i].Temp = P[i - 1].CT;
        
                P[i].CT = P[i].Temp + P[i].Bt; //use temp to calculate ct
                P[i].Tat = P[i].CT - P[i].at; // use at to calculate tat
                P[i].Wt = P[i].Tat - P[i].Bt;
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

    printf("PROCESS ID\tBURST TIME\tWAITING TIME\tCOMPLETEION TIME TIME\nTURN AROUND TIME\n");
    printf("------------------------------------------------------\n");

    for (i = 0; i < n; i++) {
        printf("%d\t\t%d\t\t%d\t\t%d\t\t%d\n", P[i].id, P[i].Bt, P[i].Wt, P[i].CT,P[i].Tat);
    }

    return 0;
}


// #include <stdio.h>

// struct Process {
//     int id, Bt, Wt, CT, at, Tat, Temp;
// } P[20], temp;

// int main() {
//     int i, n;

//     printf("Enter the Number of Processes: ");
//     scanf("%d", &n);

//     for (i = 0; i < n; i++) {
//         printf("Enter process id, burst time, and arrival time of P%d: ", i + 1);
//         scanf("%d %d %d", &P[i].id, &P[i].Bt, &P[i].at);
//     }

//     // Sort by arrival time
//     for (i = 0; i < n - 1; i++) {
//         for (int j = 0; j < n - i - 1; j++) {
//             if (P[j].at > P[j + 1].at) {
//                 temp = P[j];
//                 P[j] = P[j + 1];
//                 P[j + 1] = temp;
//             }
//         }
//     }

//     // Calculate first process values
//     if (P[0].at > 0)
//         P[0].CT = P[0].at + P[0].Bt;
//     else
//         P[0].CT = P[0].Bt;

//     P[0].Tat = P[0].CT - P[0].at;
//     P[0].Wt = P[0].Tat - P[0].Bt;

//     // Calculate the rest
//     for (i = 1; i < n; i++) {
//         if (P[i - 1].CT < P[i].at)
//             P[i].Temp = P[i].at; // idle 
//         else
//             P[i].Temp = P[i - 1].CT;

//         P[i].CT = P[i].Temp + P[i].Bt;
//         P[i].Tat = P[i].CT - P[i].at;
//         P[i].Wt = P[i].Tat - P[i].Bt;
//     }

//     // Sort back by ID
//     for (i = 0; i < n - 1; i++) {
//         for (int j = 0; j < n - i - 1; j++) {
//             if (P[j].id > P[j + 1].id) {
//                 temp = P[j];
//                 P[j] = P[j + 1];
//                 P[j + 1] = temp;
//             }
//         }
//     }

//     printf("\nPROCESS ID\tBURST TIME\tWAITING TIME\tCOMPLETION TIME\tTURN AROUND TIME\n");
//     printf("------------------------------------------------------------------------\n");
//     for (i = 0; i < n; i++) {
//         printf("%d\t\t%d\t\t%d\t\t%d\t\t%d\n", P[i].id, P[i].Bt, P[i].Wt, P[i].CT, P[i].Tat);
//     }

//     return 0;
// }
