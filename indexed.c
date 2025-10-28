#include<stdio.h>
#include <stdio.h>

int main() {
    int n, i, j, sb[20], s[20], m[20], b[20][20], x;

    printf("Enter number of files: ");
    scanf("%d", &n);

    for (i = 0; i < n; i++) {
        printf("Enter index block for file %d: ", i + 1);
        scanf("%d", &sb[i]);

        printf("Enter number of blocks occupied by file %d: ", i + 1);
        scanf("%d", &m[i]);

        printf("Enter blocks of file %d: ", i + 1);
        for (j = 0; j < m[i]; j++) {
            scanf("%d", &b[i][j]);
        }
    }

    printf("\nFile\tIndex\tLength\n");
    for (i = 0; i < n; i++) {
        printf("%d\t%d\t%d\n", i + 1, sb[i], m[i]);
    }

    printf("\nEnter file number to query: ");
    scanf("%d", &x);
    i = x - 1;

    if (i >= 0 && i < n) {
        printf("Index block: %d\n", sb[i]);
        printf("Blocks occupied: ");
        for (j = 0; j < m[i]; j++) {
            printf("%d ", b[i][j]);
        }
        printf("\n");
    } else {
        printf("Invalid file number.\n");
    }

    return 0;
}
