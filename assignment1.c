/*
 Comp 222 - Spring 2020
 Oscar Cansino
 Assignment #1: Measuring Performance
*/

#include <stdio.h>
#include <stdlib.h>


void printMenu();
void enterParameters();
void printPerformance();
void calculatePerformance();
void exit_program();

//Variables
int numberOfClasses;
float ghz = 0;
int *cpi_i;
int *count_i;
float avgCPI;
float cpuTime;
float mips;

//Main menu, starts print
int main(){
	printMenu();
	return 0;
}

void printMenu(){
	int choice;
	do{
		choice = 0;
		printf("Measuring Performance:\n");
		printf("-----------------------\n");
		printf("1) Enter Parameters\n");
		printf("2) Calculate Execution time of a sequence\n");
		printf("3) Calculate MIPS of a sequence\n");
      printf("4) Calculate average CPI of a sequence\n");
      printf("5) Exit program\n");
		printf("\nEnter selection: ");
		printf("\n");
		scanf("%d", &choice);
		switch(choice){
			case 1:
				enterParameters();
				break;
			case 2:
				printPerformance(1);
				break;
         case 3:
				printPerformance(2);
				break;
         case 4:
				printPerformance(3);
				break;
			case 5:
            exit_program();
				break;
			default:
				printf("Invalid selection\n\n");
				//in case of error
				while ((choice = getchar()) != '\n' && choice != EOF);
				break;	
		}
	}while(choice != 3);
}

void enterParameters(){
	printf("Enter the number of instruction classes: ");
	scanf("%d", &numberOfClasses);
   printf("\nEnter the frequency of the machine (GHz): ");
	scanf("%f", &ghz);
   
	cpi_i = malloc(sizeof(int)*numberOfClasses);
	count_i = malloc(sizeof(int)*numberOfClasses);
	
	for(int i=0; i<numberOfClasses; i++){
		printf("\nEnter CPI of class %i: ", i+1);
		scanf("%d", &cpi_i[i]);
		printf("\nEnter instruction count of class %i (billions): ", i+1);
		scanf("%d", &count_i[i]);
	}
	printf("\n");
}

void printPerformance(int x){
	calculatePerformance();
	if (x==1){
      printf("The execution time of the sequence is: %.2f sec\n\n", cpuTime);
   }
   if(x==2){
      printf("The MIPS of the sequence is: %.2f\n\n", mips);
      printMenu();
   }
   else if(x==3){
	   printf("The average CPI of the sequence is: %.2f\n\n", avgCPI);
   }
   
}

void calculatePerformance(){
	//Calculate Average CPI
	float InstructionCountSummation = 0.0;
	for(int i=0; i<numberOfClasses; i++){
		InstructionCountSummation+=(cpi_i[i]*(count_i[i]*1000000));
	}
	float InstructionCountSum = 0.0;
	for(int i=0; i<numberOfClasses; i++){
		InstructionCountSum+=(count_i[i]*1000000);
	}
   avgCPI = (InstructionCountSummation/1000000)/(InstructionCountSum/1000000);
	
   //Calculate CPU Time
	cpuTime = (InstructionCountSum*avgCPI*(1.0/(ghz*1000000)));

	//Calculate MIPS
   mips = ((ghz*1000)/(avgCPI));
}

void exit_program(){
   exit(0);
}
