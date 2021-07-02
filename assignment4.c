#include <stdio.h>
#include <stdlib.h>

/* declare global var's */
int MMsize, PageSize,replacement,entries,PageAddr;
int last_row = -1;

struct node{
  int vp;
  int pf;
  int accessed;
}  *pt=NULL;
typedef struct node row;

/**********************************************************************/
void option1()
{
  /* declare local var's */
  int i;
  /* Prompt for total page frame area size, individual page size, and replacement policy */
  printf("Enter main memory size (words): \n");
  scanf("%d",&MMsize);
  printf("Enter page size (words/page): \n");
  scanf("%d",&PageSize);
  printf("Enter replacement policy (0=LRU, 1=FIFO): \n");
  scanf("%d",&replacement);
  /* Allocate and initialize page table based on number of entries */
  entries=MMsize/PageSize;
  pt= (row*)malloc(entries*sizeof(row));
  for(i=0;i<entries;i++){
    pt[i].vp=-1;
    pt[i].accessed = -1;
  }

  return;
}


/**********************************************************************/
void option2()
{
  /* Declare local var's */
  int VirMemAddr,vpage,offset,i,a,PageAddr,B=pt[0].pf;
  /* Prompt for virtual address */

  printf("Enter virtual memory address to access: \n");
  scanf("%d",&VirMemAddr);

  /* Translate virtual address to virtual page and offset*/
  vpage=VirMemAddr/PageSize;
  offset=VirMemAddr%PageSize;
  int j=0;
  /* Check for end of table, unallocated entry, or matched entry in table
   while none of three cases, keep looping */
  while((j<entries)&&(pt[j].vp!=-1)&&(pt[j].vp!=vpage)){
    pt[j].accessed++;
    j++;
  }
  if(j==entries){
    a=pt[0].pf;
    for(i=0;i<=entries-2;i++){
      pt[i]=pt[i+1];
    }
    pt[entries-1].vp=vpage;
    pt[entries-1].pf=a;
    pt[entries-1].accessed = 0;
    printf("Page fault!\n");
  }
  else if(pt[j].vp==-1){
    pt[j].vp=vpage;
    pt[j].pf=j;
    pt[j].accessed = 0;
    last_row++;
    printf("Page fault!\n");
  }
  else{
  /* In case of end of table, replace either LRU or FIFO entry, print message */
    
    if(replacement==0){
      B=pt[j].pf;
      
      for(i=j; i < last_row;i++){
         pt[i]=pt[i+1];
         pt[i].accessed++;
      }
    }
    pt[i].vp=vpage;
    pt[i].pf=B;
    pt[i].accessed = 0;
    PageAddr=(B*PageSize)+offset;
    printf("Virtual address %d maps to physical address %d\n",VirMemAddr, PageAddr);
  }

  return;
}
void option3(){
  /* declare local variables */
  int i;

  /* Print*/
  printf("---------------------------\n");
  printf("| VP  | PF   | Access\n");
  printf("---------------------------\n");
  
  for(i=0;i<= last_row;i++){
    printf("| %d   | %d    | %d \n",pt[i].vp, pt[i].pf, pt[i].accessed);
    printf("---------------------------\n");

  }
}


/**********************************************************************/
int main()
{
  /* declare local var's */
  int x=0;
  while(x!=4){
    printf("\nVirtual memory to Main memory mapping\n");
    printf("--------------------------------------\n");
    printf("1) Set parameters\n");
    printf("2) Map virtual address \n");
    printf("3) Print page table\n");
    printf("4) Quit \n");
    printf("Enter Selection: \n");
    scanf("%d",&x);
    switch(x){
      case 1:option1();
      break;
      case 2:option2();
      break;
      case 3:option3();
      break;
      case 4:break;

      default: printf("invalid input please input another number\n\n");
      break;
    }
  }

  
  return 1;
}