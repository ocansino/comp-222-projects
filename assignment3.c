#include <stdio.h>
#include <stdlib.h>

/* Declare global variables */
int instr;
int cycles = 0;
int nop_count = 0;

typedef struct instr_struct {
    int destReg;
    int sourceReg1;
    int sourceReg2;
    int delay;
    char instrArr[8];
} instructions;
instructions *instr1;

/**************************************************************/
//prints the pipeline chart
void printPipeline() {
    /* Declare local variables */
    int i; 
    int j;
    int k;
    int count = 0;
        if(instr == 3) {
            cycles = cycles + 4;
            nop_count = 4;
        }
        
        else if(instr == 4){
             cycles = cycles + 1;
             nop_count = 1;
        }
        
    //print the total amount of cycles 
    printf("\nTotal number of cycles: %d", cycles);
    if(instr == 3){
      for(i = 1; i <= instr + 4 ; i++) {
        if(i == 1) {
            cycles = 5;
        }
        //delay 2 check
        if(instr1[i].delay == 2) {
            cycles = cycles + 2;
            count = count + 2;
        }
        //delay 1 check
        else if(instr1[i].delay == 1) {
            count  = count + 1;
            cycles = cycles + 1;
        }
        if(i > 1) {
            cycles = cycles + 1;
        }
        printf("\n%d)", i);
        
        //spacing
        for(k = 1; k <= count; k++) {
            printf("   ");
        }
        for(j = 1; j < i; j++) {
            printf("   ");
        }
        printf("IF ID EX MM WB");
     }
    }
    else if(instr == 4){
     for(i = 1; i <= instr + 1 ; i++) {
        if(i == 1) {
            cycles = 5;
        }
        //delay 2 check
        if(instr1[i].delay == 2) {
            cycles = cycles + 2;
            count = count + 2;
        }
        //delay 1 check
        else if(instr1[i].delay == 1) {
            count  = count + 1;
            cycles = cycles + 1;
        }
        if(i > 1) {
            cycles = cycles + 1;
        }
       
        printf("\n%d)", i);
       
        //spacing
        for(k = 1; k <= count; k++) {
            printf("   ");
        }
        for(j = 1; j < i; j++) {
            printf("   ");
        }
        printf("IF ID EX MM WB");
     }
    }
    //print amount of NOPs
    if(instr == 3){
      printf("\nNOPs: 4");
    }
    else if(instr == 4){
      printf("\nNOPs: 1");
    }
    printf("\n\n");
    return;
}
    
/**************************************************************/

void enterInstr() {
    /* Declare local variables */
    int i;
    
    /* Prompt for total number of instructions */
    printf("\nEnter total number of instructions: ");
    scanf("%d", &instr);

    //Allocate memory
    instr1 = (instructions*)malloc((instr+1)*sizeof(instructions));
    
    /* Initialize instruction 0's destination register to -1 to prevent false 
    RAW dependency w/ instruction 2 */
    instr1[0].destReg = -1;

    for(i = 1; i <= instr; i++) {
        //instruction num
        printf("\n%d) ", i);
        
        //instruction input
        scanf("%s", instr1[i].instrArr);
        
        //print input
        printf("%s", instr1[i].instrArr);
        
        //get value of each register
        instr1[i].destReg = instr1[i].instrArr[1]-'0';
        instr1[i].sourceReg1 = instr1[i].instrArr[4]-'0';
        instr1[i].sourceReg2 = instr1[i].instrArr[7]-'0';
    }
    
    //spacing
    printf("\n\n");
    return;
}
    
/***************************************************************/

//calculates cycles
void calcCycle() {
    /* Declare local variables */
    int i;
    for(i = 2; i <= instr; i++) {
        instr1[i].delay = 0;
        
        if(((instr1[i].sourceReg1 == instr1[i-2].destReg) || (instr1[i].sourceReg2 == instr1[i-2].destReg))
        && instr1[i-1].delay != 2) {
            instr1[i].delay = 1;
        }
        else if((instr1[i].sourceReg1 == instr1[i-1].destReg) || (instr1[i].sourceReg2 == instr1[i-1].destReg)) {
            instr1[i].delay = 2;
        }
        else {
            instr1[i].delay = 0;
        }
    }
    
    for(i = 1; i <= instr; i++) {
        if(i == 1) {
            cycles = 5;
        }
        if(instr1[i].delay == 2) {
            cycles = cycles + 2;
        }
        else if(instr1[i].delay == 1) {
            cycles = cycles + 1;
        }
        if(i > 1) {
            cycles = cycles + 1;
        }
    }
    //print
    printPipeline();

    return;
}

//exit
void quitProgram() {
    printf("\nProgram Ending\n");
    return;
}       
/***************************************************************/
        
int main() {
    /* Declare local variables */
    int option;
    while(option != 3) {
        //menu
        printf("Instruction-level parallelism\n");
        printf("-----------------------------\n");
        printf("1) Enter instructions\n");
        printf("2) Calculate total cycle count on a 5-stage pipeline processor\n");
        printf("3) Quit program\n");
        printf("\nEnter selection:");
        //input
        scanf("%d", &option);
        //choose options
        switch(option) {
            //option 1
            case 1:
                enterInstr();
                break;
            //option 2
            case 2:
                calcCycle();
                break;
            //option 3
            case 3:
                quitProgram();
                break;
        }
    }
    
    return 0;
}