#include <stdlib.h>
#include <stdio.h>
#include "Item.h"

Item ITEMscan(FILE *fin) {
  Item item;
  fscanf(fin,"%d %s %s", &item.prio, item.serv, item.ccli);
  return item;
}

void ITEMstore(FILE *out, Item x) {
  fprintf(out, "%d %s %s\n", x.prio, x.serv, x.ccli);
}

Item ITEMsetNull() {
  Item x = {-1, "", ""};
  return x;
}

int ITEMgreater(Item A, Item B) {
  return (KEYget(A) > KEYget(B));
}

Key KEYget(Item val){
  return val.prio;
}
