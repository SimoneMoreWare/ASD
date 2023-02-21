#include <stdio.h>
#include <stdlib.h>
#include "Item.h"
#include "IBST.h"

int  main() {
  Item item, item1;
  int i, cont;
  IBST ibst;

  ibst = IBSTinit();
  cont = 1;
  while(cont) {
    printf("\nOperations on IBSTs\n");
    printf("===============\n");
    printf("1.Insert\n");
    printf("2.Search\n");
    printf("3.Preorder visit\n");
    printf("4.Postorder visit\n");
    printf("5.Inorder visit\n");
    printf("6.Size\n");
    printf("7.Delete \n");
    printf("8.Destroy \n");
    printf("9.Exit\n");
    printf("Enter your choice : ");
    if(scanf("%d",&i)<=0) {
      printf("Integers only!\n");
      exit(0);
    }
    else {
      switch(i) {
                case 1:     printf("Enter interval: \n");
                            item = ITEMscan();
                            IBSTinsert(ibst,item);
                            break;
                case 2:     printf("Enter interval: \n");
                            item = ITEMscan();
                            item1 = IBSTsearch(ibst,item);
                            if (ITEMcheckNull(item1))
                                printf("Overlapping interval not found!\n");
                            else {
                                printf("Overlapping interval found! ");
                                ITEMstore(item1);
                            }
                            break;
                case 3:     printf("Preorder visit:\n");
                            IBSTvisit(ibst, PREORDER);
                            break;
                case 4:     printf("Postorder visit:\n");
                            IBSTvisit(ibst, POSTORDER);
                            break;
                case 5:     printf("Inorder visit:\n");
                            IBSTvisit(ibst, INORDER);
                            break;
                case 6:     printf("The IBST contains %d distinct items\n", IBSTcount(ibst));
                            break;
                case 7:    if(IBSTempty(ibst))
                             printf("IBST is empty\n");
                            else {
                              printf("Enter interval: \n");
                              item = ITEMscan();
                              IBSTdelete(ibst,item);
                            }
                            break;
                case 8:     printf("\nIBST destroyed!\n");
                            cont = 0;
                            IBSTfree(ibst);
                            break;
                case 9:     cont = 0;
                            IBSTfree(ibst);
                            break;
                default:    printf("Invalid option\n");
      }
    }
  }
  return 0;
}
