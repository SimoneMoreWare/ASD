#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "Item.h"

static char buf[MAXC];

struct item { char *str; int value; };

Item ITEMnew() {
  Item val=(Item) malloc(sizeof(struct item));
  if (val==NULL)
    return NULL;
  val->str = NULL;
  val->value = 0;
  return val;
}

Item ITEMscan(FILE *fp) {
  Item val;
  if (fp == NULL) return NULL;
  val = ITEMnew();
  if (val != NULL) {
    fscanf(fp, "%s %d", buf, &val->value);
    val->str = strdup(buf);
    if (val->str == NULL) return NULL;
  }
  return val;
}

void ITEMstore(FILE *fp, Item val) {
  if (fp == NULL) return;
  fprintf(fp, "%s %d\n", val->str, val->value);
}

int ITEMcompare (Item val1, Item val2) {
  Key k1 = KEYget(val1), k2 = KEYget(val2);
  return KEYcompare(k1, k2);
}

void ITEMfree(Item val) {
  if (val == NULL)
    return;
  free(val->str);
  free(val);
}

Item ITEMsetNull() {
  return NULL;
}

int ITEMcheckNull(Item val) {
  if (val == NULL)
    return 1;
  else
    return 0;
}

Key KEYscan() {
  Key k;
  scanf("%s", buf);
  k = strdup(buf);
  if (k == NULL) return NULL;
  return k;
}

void KEYfree(Key k) {
  if (k == NULL) return;
  free(k);
}

char *KEYdisplay(Key k) {
  return k;
}

int KEYcompare(Key k1, Key k2) {
  return strcmp(k1, k2);
}

Key KEYget(Item val) {
  if (val == NULL)
    return NULL;
  return val->str;
}

