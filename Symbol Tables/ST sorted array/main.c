#include <stdio.h>
#include <stdlib.h>
#include "Item.h"
#include "ST.h"

int main(int argc, char *argv[]) {
  int i, r, cont, maxN;
  Item data;
  Key k;
  ST st;

  if (argc !=2) {
    printf("Error in command line, correct format: \n");
    printf("client <maximum number of data> \n");
    exit(1);
  }

  maxN = atoi(argv[1]);

  st = STinit(maxN);

  cont = 1;
  while(cont) {
    printf("\nOperations on Symbol Tables (item: string of 2 capital letters)\n");
    printf("===============\n");
    printf("1.Insert item \n");
    printf("2.Search for item with given key \n");
    printf("3.Delete item with given key \n");
    printf("4.Select item with given rank \n");
    printf("5.Display Symbol Table \n");
    printf("6.Display Symbol Table Size \n");
    printf("7.Destroy Symbol Table \n");
    printf("8.Exit\n");
    printf("Enter your choice : ");
    if(scanf("%d",&i)<=0) {
      printf("Integers only!\n");
      exit(0);
    }
    else {
      switch(i) {
        case 1:     printf("\nEnter data: \n");
                    data = ITEMscan();
                    k = KEYget(&data);
                    if (ITEMcheckNull(STsearch(st, k)))
                      STinsert(st, data);
                    break;
        case 2:     printf("\nEnter key: \n");
                    data = ITEMscan();
                    k = KEYget(&data);
                    if (ITEMcheckNull(STsearch(st, k)))
                      printf("key not found!\n");
                    else
                      printf("key found!\n");
                    break;
        case 3:     printf("\nEnter key: \n");
                    data = ITEMscan();
                    k = KEYget(&data);
                    if (ITEMcheckNull(STsearch(st, k)))
                      printf("data not found!\n");
                    else
                      STdelete(st, k);
                    break;
        case 4:     printf("\nEnter rank: ");
                    scanf("%d", &r);
                    if (r >= STcount(st))
                      printf("rank outside range \n");
                    else {
                      printf("Data of rank %d is: ", r);
                      ITEMstore(STselect(st, r));
                    }
                    break;
        case 5:     if (st==NULL)
                      printf("Symbol table doesn't exist!\n");
                    else
                      if (STcount(st)==0)
                        printf("\nSymbol Table empty!\n");
                      else
                        STdisplay(st);
                    break;
        case 6:     if (st==NULL)
                      printf("Symbol table doesn't exist!\n");
                    else if (STcount(st)==0)
                        printf("\nSymbol Table empty!\n");
                    else
                      printf("\nThe Symbol Table contains %d distinct data\n", STcount(st));
                    break;
        case 7:     printf("\nSymbol Table destroyed!\n");
                    STfree(st);
                    cont = 0;
                    break;
        case 8:     cont = 0;
                    break;
        default:    printf("\nInvalid option\n");
      }
    }
  }
  return 0;
}

