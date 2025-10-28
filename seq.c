#include <stdio.h>
void main(){
    int mem[50],max=50;
    int files,start,block;
    for(int i=0;i<max;i++){
        mem[i]=-1;
    }
    int ch=1;
    while(ch){
    printf("enter number of files:");
    scanf("%d",&files);
    for(int i=0;i<files;i++){
        printf("enter the starting block of file %d:",i+1);
        scanf("%d",&start);
        if(start>=max){
            printf("exceeded block\n");
            break;
        }
        if(mem[start]==1){
            printf("block %d already occupied\n",start);
            break;
        }
        printf("enter the number of blocks for file %d:",i+1);
        scanf("%d",&block);
        for(int j=start;j<start+block;j++){
            if(j>=max){
                printf("exceeded block\n");
                break;
            }
            if(mem[j]==-1){
                mem[j]=1;
                printf("allocated block %d for file %d\n",j,i+1);
            }else{
                printf("block %d already occupied\n",j);
                break;
            }
            
        }
    }
    printf("Do you want to continue? (1/0): ");
    scanf("%d",&ch);
}
}