#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "Item.h"
#include "ST.h"

int main() {
  Item item;
  Key k;
  int i,  cont, maxN;
  ST st;
  printf("Input size of hash table to guarantee load factor < 1/2:");
  scanf("%d", &maxN);

  st = STinit(maxN);
  cont = 1;

  while(cont) {
    printf("\nOperations on hash tables\n");
    printf("===============\n");
    printf("1.Insert\n");
    printf("2.Search for item with given key\n");
    printf("3.Delete item with given key\n");
    printf("4.Number of entries\n");
    printf("5.Display\n");
    printf("6.Destroy\n");
    printf("7.Exit\n");
    printf("Enter your choice : ");
    if(scanf("%d",&i)<=0) {
      printf("Integers only!\n");
      exit(0);
    }
    else {
      switch(i) {
                case 1:     printf("Enter item: \n");
                            item = ITEMscan();
                            if (ITEMcheckNull(STsearch(st, KEYget(&item))))
                              STinsert(st, item);
                            break;
                case 2:     printf("Enter item: \n");
                            item = ITEMscan();
                            if (ITEMcheckNull(STsearch(st, KEYget(&item))))
                              printf("data with given key not found!\n");
                            else
                              printf("data with given key found!\n");
                            break;
                case 3:     printf("Enter item: \n");
                            item = ITEMscan();
                            k = KEYget(&item);
                            if (ITEMcheckNull(STsearch(st, k)))
                              printf("data with given key not in symbol table!\n");
                            else
                              STdelete(st, k);
                            break;
                case 4:     if (st==NULL)
                              printf("Symbol table doesn't exist!\n");
                            else if (STempty(st)==1)
                              printf("\nSymbol Table empty!\n");
                            else
                              printf("\nSymbol Table currently contains %d entries\n", STcount(st));
                            break;
                case 5:     if (st==NULL)
                              printf("Symbol table doesn't exist!\n");
                            else
                              if (STempty(st)==1)
                                printf("\nSymbol Table empty!\n");
                            else
                              STdisplay(st);
                            break;
                case 6:     printf("\nSymbol Table destroyed!\n");
                            STfree(st);
                            cont = 0;
                            break;
                case 7:     cont = 0;
                            break;
                default:    printf("Invalid option\n");
            }
      }
    }
  return 0;
}
