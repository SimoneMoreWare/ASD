#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Item.h"

Item ITEMscan() {
  Item val;
  printf("name = "); scanf("%s", val.name);
  printf("priority = "); scanf("%d", &val.prio);
  return val;
}

void ITEMstore(Item val) {
  printf("name = %s priority = %d  ", val.name, val.prio);
}

Item ITEMsetNull(){
  Item val = {"", -1};
  return val;
}

Name NAMEget(Item *pval) {
  return pval->name;
}

int NAMEcmp(Name n1, Name n2) {
  return strcmp(n1, n2);
}

int  PRIOget(Item val) {
  return val.prio;
}

