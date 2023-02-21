#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Item.h"

Item ITEMscan() {
  Item val;
  printf("name and value: ");
  scanf("%s %d", val.name, &(val.value));
  return val;
}

void ITEMstore(Item val) {
  printf("name: %s value: %d ", val.name, val.value);
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

Key KEYget(Item *pval) {
  return pval->name;
}

int KEYcmp(Key k1, Key k2) {
  return strcmp(k1, k2);
}

