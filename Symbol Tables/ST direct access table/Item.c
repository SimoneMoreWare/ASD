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

Key KEYget(Item *pval) {
  return pval->name;
}

int GETindex(Key k) {
  int i = 0, b = 26;

  for ( ; *k != '\0'; k++)
    i = (b * i + (*k - ((int) 'A')));
  return i;
}
