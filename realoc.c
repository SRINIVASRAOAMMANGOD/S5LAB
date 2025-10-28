#include<stdio.h> 
#include<string.h> 
#include<stdlib.h> 
void main() 
{ 
    char add[10],length[10],input[10],binary[10],bitmask[10],relocbit; 
    int start,inp,len,i,address,opcode,addr,actualadd; 
    FILE *fp1,*fp2; 
    printf("ENTER THE ACTUAL STARTING ADDRESS:"); 
    scanf("%d",&start); 
    fp1=fopen("input1.txt","r"); 
    fp2=fopen("output1.txt","w"); 
    fscanf(fp1,"%s",input); 
    while(strcmp(input,"E")!=0){ 
        if(strcmp(input,"H")==0){ 
            fscanf(fp1,"%s",add); 
            fscanf(fp1,"%s",length); 
            fscanf(fp1,"%s",input); 
        } 
        if(strcmp(input,"T")==0){ 
            fscanf(fp1,"%d",&address); 
            fscanf(fp1,"%s",bitmask); 
            address+=start; 
            len=strlen(bitmask); 
            for(i=0;i<len;i++){ 
                fscanf(fp1,"%d",&opcode); 
                fscanf(fp1,"%d",&addr); 
                relocbit=bitmask[i]; 
                if(relocbit=='0') 
                    actualadd=addr; 
                else 
                    actualadd=addr+start; 
                fprintf(fp2,"%d\t%d\t%d\n",address,opcode,actualadd); 
                address+=3; 
            } 
            fscanf(fp1,"%s",input); 
        } 
    } 
    fclose(fp1); 
    fclose(fp2); 
    printf("FINISHED"); 
}