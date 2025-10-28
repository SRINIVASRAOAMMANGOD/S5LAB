#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void main() {
    char symbol[20], label[10], opcode[10], operand[10], code[10], mnemonic[10],
         add[50], objectcode[20], character;
    int flag, flag1, locctr, location, loc;
    FILE *fp1, *fp2, *fp3, *fp4;

    fp1 = fopen("out3.txt", "r");
    fp2 = fopen("twocod.txt", "w");
    fp3 = fopen("cocode.txt", "r");
    fp4 = fopen("sym1.txt", "r");

    fscanf(fp1, "%d%s%s%s", &locctr, label, opcode, operand);

    if (strcmp(opcode, "START") == 0) {
        fprintf(fp2, "%s\t%s\t%s\t%s\n", label, opcode, operand);
        fscanf(fp1, "%d%s%s%s", &locctr, label, opcode, operand);
    }

    while (strcmp(opcode, "END") != 0) {
        flag = 0;

        fscanf(fp3, "%s\t%s", code, mnemonic);
        while (strcmp(code, "END") != 0) {
            if ((strcmp(opcode, code) == 0) && (strcmp(mnemonic, "*") != 0)) {
                flag = 1;
                break;
            }
            fscanf(fp3, "%s\t%s", code, mnemonic);
        }

        if (flag == 1) {
            flag1 = 0;
            rewind(fp4);

            while (!feof(fp4)) {
                fscanf(fp4, "%s%d", symbol, &loc);
                if (strcmp(symbol, operand) == 0) {
                    flag1 = 1;
                    break;
                }
            }

            if (flag1 == 1) {
                sprintf(add, "%d", loc);
                strcpy(objectcode, strcat(mnemonic, add));
            }
        } else if (strcmp(opcode, "BYTE") == 0 || strcmp(opcode, "WORD") == 0) {
            if ((operand[0] == 'C') || (operand[0] == 'X')) {
                character = operand[2];
                sprintf(add, "%d", character);
                strcpy(objectcode, add);
            } else {
                strcpy(objectcode, add);
            }
        } else {
            strcpy(objectcode, "(0)");
        }

        fprintf(fp2, "%s\t%s\t%s\t%d\t%s\n", label, opcode, operand, locctr, objectcode);
        fscanf(fp1, "%d%s%s%s", &locctr, label, opcode, operand);
    }

    fprintf(fp2, "%s\t%s\t%s\t%d\n", label, opcode, operand, locctr);

    fclose(fp1);
    fclose(fp2);
    fclose(fp3);
    fclose(fp4);

    printf("The object code is:\n");

    fp2 = fopen("twouut.txt", "r");
    char ch = fgetc(fp2);

    while (ch != EOF) {
        printf("%c", ch);
        ch = fgetc(fp2);
    }

    fclose(fp2);
}
