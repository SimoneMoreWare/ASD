#include <stdio.h>
#include <stdlib.h>
#include "Item.h"

Item ITEMscan() {
  Item item;
  printf("x = ");
  scanf("%d", &item.x);
  printf("y = ");
  scanf("%d", &item.y);
  return item;
}

void ITEMshow(Item item) {
  printf("(%d  %d) \n", item.x, item.y);
}


Item ITEMrand() {
  Item item;
  item.x = maxKey*((float)rand()/RAND_MAX);
  item.y = maxKey*((float)rand()/RAND_MAX);
  return item;
}

int ITEMeq(Item A, Item B) {
  return (A.x == B.x);
}

int ITEMneq(Item A, Item B) {
  return (A.x != B.x);
}


int ITEMlt(Item A, Item B) {
  return (A.x < B.x);
}

int ITEMgt(Item A, Item B) {
  return (A.x > B.x);
}

