#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "Item.h"

Item ITEMscan() {
  Item val;
  printf("name and value: ");
  scanf("%s %d", val.name, &(val.value));
  return val;
}

Item ITEMrand() {
  Item tmp = {"", -1};
  tmp.value = 100*(1.0 * rand()/RAND_MAX);
  return tmp;
}

void ITEMstore(Item val) {
  printf("name: %s value: %d\n", val.name, val.value);
}

Item ITEMsetNull() {
  Item val = {"", -1};
  return val;
}

int  KEYcmp(Key k1, Key k2) {
  if (k1 < k2)
    return -1;
  else if ( k1 == k2)
    return 0;
  return 1;
}

Key KEYget(Item val) {
  return val.value;
}


