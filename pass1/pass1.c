#include<stdio.h>
#include<stdlib.h>
#include<string.h>

void main(){
 FILE *optab,*input,*symtab,*intermediate,*programlength;
 int locctr,start,program_length;
 char label[20],opcode[20],operand[20],mneumonic[20],code[20];
 input=fopen("input.txt","r");
 optab=fopen("optab.txt","r");
 symtab=fopen("symtab.txt","w");
 intermediate=fopen("intermediate.txt","w");
 programlength=fopen("programlength.txt","w");
 if(input==NULL||optab==NULL||symtab==NULL||intermediate==NULL){
  printf("ERROR OPENING FILE!\n");
  exit(0);
 }
 fscanf(input,"%s%s%s",label,opcode,operand);
 if(strcmp(opcode,"START")==0){
  start=atoi(operand);
  locctr=start;
  fprintf(intermediate,"\t\t%s   %s\n",opcode,operand);
 }
 else{
  locctr=0;
 }
 printf("LOCCTR:\n%d\n",locctr);
 fscanf(input,"%s%s%s",label,opcode,operand);
 while(strcmp(opcode,"END")!=0){
  fprintf(intermediate,"%d\t%s\t%s\t%s\n",locctr,label,opcode,operand);
  fscanf(optab,"%s%s",mneumonic,code);
  if(strcmp(label,"***")!=0){
   fprintf(symtab,"%s\t%d\n",label,locctr);
  }
  if(strcmp(opcode,"WORD")==0){
   locctr+=3;
  }
  else if(strcmp(opcode,"RESW")==0){
   locctr+=(3*atoi(operand));
  }
  else if(strcmp(opcode,"RESB")==0){
   locctr+=atoi(operand);
  }
  else if(strcmp(opcode,"BYTE")==0){
   locctr+=(strlen(operand)-3);
  }
  else if(strcmp(opcode,mneumonic)==0){
   locctr+=3;
  }
  printf("%d\n",locctr);
  fscanf(input,"%s%s%s",label,opcode,operand);
 }
 fprintf(intermediate,"%d\t%s\t%s\t%s\n",locctr,label,opcode,operand);
 program_length=locctr-start;
 printf("Program_length=%d\n",program_length);
 fprintf(programlength,"%d",program_length);
 fclose(input);
 fclose(optab);
 fclose(symtab);
 fclose(intermediate);
}
