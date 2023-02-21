#include <stdio.h>
#include <stdlib.h>
#include "Item.h"

Item ITEMscan() {
  Item item;
  printf("Input name, size and value: ");
  scanf("%s %d %d", item.name, &(item.size), &(item.value));
  return item;
}

void ITEMshow(Item item) {
  printf("%s ", item.name);
}
