#include <stdio.h>

#include <stdlib.h>

#include <string.h>

#include <math.h>

#include "Item.h"



static char buf[MAXC];



Item ITEMscan(FILE *fp) {
  fscanf(fp, "%s", buf);

  return ITEMnew(buf, START);
}

Item ITEMnew(Id id, int prio) {

  Item item;

  item.value = prio;

  strcpy(item.name, id);

  return item;

}



void ITEMstore(FILE *fp, Item val) {

  fprintf(fp, "name = %s priority = %d  \n", val.name, val.value);

}





int ITEMless (Item val1, Item val2) {

  Key k1 = KEYget(val1), k2 = KEYget(val2);

  if (KEYcompare(k1, k2) == -1)

    return 1;

  else

    return 0;

}



int ITEMgreater(Item val1, Item val2) {

  Key k1 = KEYget(val1), k2 = KEYget(val2);

  if (KEYcompare(k1, k2) == 1)

    return 1;

  else

    return 0;

}



void ITEMchange(Item *val1, Item *val2, float ratio) {

  val1->value += (int) ceil(val2->value * ratio);

  val2->value  = (int) floor(val2->value*(1-ratio));

}



int ITEMzero(Item val) {

  return (val.value == 0);

}



int  KEYcompare(Key k1, Key k2) {

  if (k1 < k2)

    return -1;

  else if ( k1 == k2)

    return 0;

  else

    return 1;

}



Key KEYget(Item val) {

  return val.value;

}



int  IDcompare(Id i1, Id i2) {

  return strcmp(i1, i2);

}



void GETid(Item val, Id id) {

  strcpy(id, val.name);

}



void SCANid(Id id) {

  scanf("%s", id);

}

