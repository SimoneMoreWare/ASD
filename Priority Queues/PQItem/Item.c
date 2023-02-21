#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "Item.h"

Item ITEMscan() {
  Item val;
  printf("name and priority: ");
  scanf("%s %d", val.name, &(val.prio));
  return val;
}

void ITEMstore(Item val) {
  printf("name: %s priority: %d\n", val.name, val.prio);
}

int  KEYcmp(Key k1, Key k2) {
  if (k1 < k2)
    return -1;
  else if ( k1 == k2)
    return 0;
  return 1;
}

Key KEYget(Item val) {
  return val.prio;
}

