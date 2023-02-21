#include <stdio.h>
#include <stdlib.h>
#include "Item.h"


Item ITEMscan() {
  Item A;
  printf("name, start, stop: ");
  scanf("%s %d %d", A.name, &(A.start), &(A.stop));
  return A;
}

void ITEMstore(Item A) {
  printf("name= %s \t start= %d \t stop = %d \n", A.name, A.start, A.stop);
}

int ITEMlt(Item A, Item B) {
  return (A.stop < B.stop);
}

int ITEMeq(Item A, Item B) {
  return (A.stop == B.stop);
}

Key KEYgetStop(Item A) {
  return A.stop;
}

Key KEYgetStart(Item A) {
  return A.start;
}

Key KEYgetSel(Item A) {
  return A.selected;
}

void KEYsetSel(Item *pA){
  pA->selected = 1;
}
