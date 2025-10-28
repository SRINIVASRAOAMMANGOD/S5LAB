#include<stdio.h>
#include<conio.h>

struct file {
    int start, size, block[10];
} f[10];

void main() {
    int i, j, n;
    
    printf("Enter no. of files:");
    scanf("%d", &n);
    
    for(i = 0; i < n; i++) {
        printf("Enter starting block of file %d:", i+1);
        scanf("%d", &f[i].start);
        f[i].block[0] = f[i].start;
        printf("Enter no.of blocks:");
        scanf("%d", &f[i].size);
        printf("Enter block numbers:");
        for(j = 1; j <= f[i].size; j++) {
            scanf("%d\n", &f[i].block[j]);
        }
    }
    
    printf("Start\tsize\tblock\n");
    
    for(i = 0; i < n; i++) {
        printf("File %d:\t", i+1);
        printf("%d\t%d\t", f[i].start, f[i].size);
        for(j = 1; j <= f[i].size-1; j++) {
            printf("%d--->", f[i].block[j]);
        }
        printf("%d", f[i].block[j]);
        printf("\n");
    }
   
}