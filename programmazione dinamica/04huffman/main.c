#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Item.h"
#include "Tree.h"
#include "PQ.h"

int main(int argc, char *argv[]) {
  int i, maxN;
  Tree t, tL, tR;
  PQ pq;

  if (argc < 2) {
    printf("Error: missing argument\n");
    printf("correct format:\n");
    printf("%s maxN \n", argv[0]);
    return 1;
  }

  maxN = atoi(argv[1]);

  pq = PQinit(maxN);

  for (i=0; i<maxN; i++) {
    t = TREErootCreate(ITEMscan());
    PQinsert(pq, t);
  }

  while (PQsize(pq) > 1) {
    tL = PQextractMin(pq);
    tR = PQextractMin(pq);
    t = TREEjoin(tL, tR);
    PQinsert(pq, t);
  }

  t =PQextractMin(pq);

  printf("\nHuffman's code is:\n");
  TREEdisplayCode(t);

  PQfree(pq);

  return 0;
}

