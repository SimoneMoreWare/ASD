#include <stdio.h>
#include <stdlib.h>
#include "Item.h"
#include "PQ.h"

int main(int argc, char *argv[]) {
  int i, pos, cont, maxN;
  Item item;
  PQ a;
  if (argc < 2) {
    printf("Error: missing argument\n");
    printf("correct format:\n");
    printf("%s maxN \n", argv[0]);
    return 0;
  }

  cont = 1;
  maxN = atoi(argv[1]);

  a = PQinit(maxN);

  while(cont) {
    printf("\nOperations on a priority queue\n");
    printf("===============\n");
    printf("1.Insert item \n");
    printf("2.Extract maximum \n");
    printf("3.Display maximum\n");
    printf("4.Size of priority queue\n");
    printf("5.Display priority queue\n");
    printf("6.Change priority\n");
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
                    PQinsert(a, item);
                    break;
        case 2:     if (PQempty(a))
                      printf("\nCannot extract from empty priority queue!\n");
                    else
                      ITEMstore(PQextractMax(a));
                    break;
        case 3:     if (PQempty(a))
                      printf("\n Priority queue is empty!\n");
                    else
                      ITEMstore(PQshowMax(a));
                    break;
        case 4:     printf("\nSize of priority queue is: %d\n", PQsize(a));
                    break;
        case 5:     if (PQempty(a))
                      printf("\n Priority queue is empty!\n");
                    else
                      PQdisplay(a);
                    break;
        case 6:     printf("Enter position:");
                    scanf("%d", &pos);
                    printf("Enter new item: \n");
                    item = ITEMscan();
                    PQchange(a, pos, item);
                    break;
        case 7:     cont = 0;
                    PQfree(a);
                    break;
        default:    printf("Invalid option\n");
      }
    }
  }
  return 0;
}
