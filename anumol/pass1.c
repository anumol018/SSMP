#include<stdio.h>
#include<string.h>
#include<stdlib.h>
void main(){
FILE *input, *optab, *symtab, *intermediate;
int locctr, start, flag, program_length;
char opcode[20], operand[20], label[20], mneumonic[20], code[20];
input = fopen("input.txt", "r");
optab = fopen("optab.txt", "r");
symtab = fopen("symtab.txt", "w");
intermediate = fopen("intermediate.txt", "w");
if (input == NULL || optab == NULL || symtab == NULL || intermediate == NULL) { 
printf("Error opening file!\n");
exit(0);
}
fscanf(input, "%s %s %s", label, opcode, operand);
if (strcmp(opcode, "START") == 0) {
start = atoi(operand);
locctr = start;
fprintf(intermediate, "     %s\t%s\n", opcode, operand);
} 
else {
locctr = 0;
}
printf("LOCCTR:\n%d\n",locctr);
fscanf(input, "%s %s %s", label, opcode, operand);
while (strcmp(opcode, "END") != 0) {
fprintf(intermediate, "%d\t%s\t%s\t%s\n", locctr, label, opcode, operand);
flag = 0;
if (strcmp(label, "**") != 0) {
fprintf(symtab, "%s\t%d\n", label, locctr);
} 
if (strcmp(opcode, "WORD") == 0) {
locctr += 3;
} 
else if (strcmp(opcode, "RESW") == 0) {
locctr += (3 * atoi(operand));
} 
else if (strcmp(opcode, "RESB") == 0) {
locctr += atoi(operand);
}
else if (strcmp(opcode, "BYTE") == 0) {
locctr += (strlen(operand)-3);
} 
else {
locctr += 3;
flag = 1;
}
printf("%d\n",locctr);
fscanf(input, "%s %s %s", label, opcode, operand);
}
fprintf(intermediate, "%d\t%s\t%s\t%s\n",locctr,label, opcode, operand);
program_length = locctr - start;
printf("Program Length = %d\n", program_length);
fclose(input);
fclose(intermediate);
fclose(symtab);
fclose(optab);
}
