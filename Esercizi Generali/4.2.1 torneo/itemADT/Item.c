#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "Item.h"

#define START 10

static char buf[MAXC];

struct item { char *name; int value; };

Item ITEMscan(FILE *fp) {
  fscanf(fp, "%s", buf);
  return ITEMnew(buf, START);
}

Item ITEMnew(Id id, int prio) {
  Item item = calloc(1, sizeof(*item));
  if (item == NULL)
    return NULL;
  item->value = prio;
  item->name = strdup(id);
  if (item->name == NULL) return NULL;
  return item;
}

void ITEMfree(Item val) {
  if (val->name!=NULL)
    free(val->name);
  free(val);
}

void ITEMstore(FILE *fp, Item val) {
  fprintf(fp, "name = %s priority = %d  \n", val->name, val->value);
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

void ITEMchange(Item val1, Item val2, float ratio) {
  if (val1 == NULL || val2 == NULL)
    return;
  val1->value += (int) ceil(val2->value * ratio);
  val2->value  = (int) floor(val2->value*(1-ratio));
}

int ITEMzero(Item val) {
  if (val == NULL)
    return 0;
  return (val->value == 0);
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
  return val->value;
}

Id GETid(Item val) {
  return val->name;
}

Id SCANid() {
  scanf("%s", buf);
  return strdup(buf);
}

int  IDcompare(Id i1, Id i2) {
  return strcmp(i1, i2);
}

