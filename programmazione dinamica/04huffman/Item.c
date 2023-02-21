#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Item.h"

Item ITEMscan() {
  Item val;
  printf("letter, frequency: ");
  scanf("%s %d", val.let, &(val.freq));
  return val;
}

void ITEMstore(Item val) {
  printf("letter, frequency: %s %d\n", val.let, val.freq);
}

Item ITEMmerge(Item val1, Item val2) {
  Item val;
  strcpy(val.let, "");
  val.freq = val1.freq + val2.freq;
  return val;
}

int ITEMgt (Item val1, Item val2) {
  return (val1.freq > val2.freq);
}

int ITEMlt (Item val1, Item val2) {
  return (val1.freq < val2.freq);
}

Let  LETget(Item *pval) {
  return (pval->let);
}
