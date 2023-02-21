#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "Item.h"

Item ITEMscan() {
  Item val;
  printf("name and value: ");
  scanf("%s %d", val.name, &(val.value));
  return val;
}

void ITEMstore(Item val) {
  printf("name: %s value: %d\n", val.name, val.value);
}

int ITEMcheckNull(Item val) {
  if (strcmp(val.name, "")==0)
    return 1;
  return 0;
}

Item ITEMsetNull() {
  Item val = {"", -1};
  return val;
}

Key KEYscan() {
  Key k;
  scanf("%d", &k);
  return k;
}

Key KEYget(Item val) {
  return val.value;
}

int KEYcmp(Key k1, Key k2){
  if (k1>k2)
    return 1;
  else if (k1==k2)
    return 0;
  return -1;
}

