#include<stdio.h>
#include<string.h>
#include<stdlib.h>
int main(){
    char ch,label[10],opcode[10],operand[10],code[10],mnemonics[10],read[50];
    int start,length,locctr;
    FILE *fp1,*fp2,*fp3,*fp4;
    fp1=fopen("i.txt","r");
    fp2=fopen("o.txt","r");
    fp3=fopen("systab.txt","w");
    fp4=fopen("inter.txt","w");
    fscanf(fp1,"%s\t%s\t%s",label,opcode,operand);
    if(strcmp(opcode,"START")==0){
        start=atoi(operand);
		locctr=start;
		fprintf(fp4,"*\t%s\t%s\t%s\n",label,opcode,operand);
		fscanf(fp1,"%s\t%s\t%s",label,opcode,operand);
   }
else locctr=0;
printf("\n%d and %d\n",start,locctr);
while(strcmp(opcode,"END")!=0){
	fprintf(fp4,"%d\t",locctr);
	if(strcmp(label,"**")!=0){
		fprintf(fp3,"%s\t%d\n",label,locctr);
	}
	fscanf(fp2,"%s\t%s",mnemonics,code);
	while(strcmp(mnemonics,"END")!=0){
		if(strcmp(opcode,mnemonics)==0){
		
			locctr+=3;
			break;
		}
	fscanf(fp2,"%s\t%s",mnemonics,code);		
	}	


if(strcmp(opcode,"WORD")==0){
	locctr+=3;
}else if(strcmp(opcode,"RESW")==0){
    locctr+=(3*atoi(operand));
}else if(strcmp(opcode,"RESB")==0){
    locctr+=atoi(operand);
}else if(strcmp(opcode,"BYTE")==0){
    locctr+=1;
}



fprintf(fp4,"%s\t%s\t%s\n",label,opcode,operand);
fscanf(fp1,"%s\t%s\t%s\n",label,opcode,operand);
if((strcmp(opcode,"END")==0)){
	fprintf(fp4,"%d\t",locctr);
	fprintf(fp4,"%s\t%s\t%s\n",label,opcode,operand);
}

}	
printf("\n%d and %d\n",start,locctr);
length=locctr-start;
printf("\n%d\n",length);
fclose(fp1);

fclose(fp2);

fclose(fp3);

fclose(fp4);

printf("intermediate file conent\n");
fp4=fopen("inter.txt","r");
ch=fgetc(fp4);
while(ch!=EOF){
	printf("%c",ch);
	ch=fgetc(fp4);	
}
printf("\nsymtab file conent\n");
fp3=fopen("systab.txt","r");
ch=fgetc(fp3);
while(ch!=EOF){
	printf("%c",ch);
	ch=fgetc(fp3);
}
fclose(fp3);
fclose(fp4);
return 0;
}