#include <stdio.h>
#include <stdlib.h>
#include "Item.h"
#include "PQ.h"

int main(int argc, char *argv[]) {
  int i, cont, maxN;
  Item item;
  PQ pq;
  if (argc < 2) {
    printf("Error: missing argument\n");
    printf("correct format:\n");
    printf("%s maxN \n", argv[0]);
    return 0;
  }

  cont = 1;
  maxN = atoi(argv[1]);

  pq = PQinit(maxN);

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
                    PQinsert(pq, item);
                    break;
        case 2:     if (PQempty(pq))
                      printf("\nCannot extract from empty priority queue!\n");
                    else
                      ITEMstore(PQextractMax(pq));
                    break;
        case 3:     if (PQempty(pq))
                      printf("\n Priority queue is empty!\n");
                    else
                      ITEMstore(PQshowMax(pq));
                    break;
        case 4:     printf("\nSize of priority queue is: %d\n", PQsize(pq));
                    break;
        case 5:     if (PQempty(pq))
                      printf("\n Priority queue is empty!\n");
                    else
                      PQdisplay(pq, maxN);
                    break;
        case 6:     printf("Enter new item: \n");
                    item = ITEMscan();
                    PQchange(pq, item);
                    break;
        case 7:     cont = 0;
                    PQfree(pq);
                    break;
        default:    printf("Invalid option\n");
      }
    }
  }
  return 0;
}
