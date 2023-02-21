#include <stdio.h>
#include <stdlib.h>
#include "Item.h"

Item ITEMscan()
{
    Item item;
    printf("x = ");
    scanf("%d", &item.x);
    return item;

}

void ITEMshow(Item item)
{
    printf("%6d\n", item.x);
}

Key key(Item item)
{
    return item.x;
}


Item ITEMrand()
{
    Item item = { maxKey*rand()/RAND_MAX};
    return item;

}

int ITEMeq(Item A, Item B) {
  return (key(A) == key(B));
}

int ITEMneq(Item A, Item B) {
  return (key(A) != key(B));
}

int ITEMlt(Item A, Item B) {
  return (key(A) < key(B));
}

int ITEMgt(Item A, Item B) {
  return (key(A) > key(B));
}

