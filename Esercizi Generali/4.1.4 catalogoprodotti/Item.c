#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Item.h"

static char buf[MAXC];

struct item {
  float price;
  char *str;
};

Item ITEMnew() {
  Item val=(Item) malloc(sizeof(struct item));
  if (val==NULL)
    return NULL;
  val->str = NULL;
  val->price = 0;
  return val;
}

void ITEMfree(Item x) {
  if (x == NULL)
    return;
  if (x->str != NULL)
    free(x->str);
  free(x);
}

Item ITEMscan(FILE *fin) {
  Item val;
  float price;
  if (fin == NULL)
    return NULL;
  if (fin == stdin)
    printf("Input name and price of product: ");
  if (fscanf(fin, "%s %f", buf, &price) != 2) 
    return NULL;
  val = ITEMfill(buf, price);
  return val;
}

Item ITEMfill(char *str, float price) {
  Item tmp;
  tmp = ITEMnew();
  if (tmp == NULL)
    return NULL;
  if (tmp != NULL) {
    tmp->str = strdup(str);
    if (tmp->str == NULL)
      return NULL;
    tmp->price = price;
  }
  return tmp;
}

void ITEMstore(FILE *fout, Item x) {
  if (x != NULL)
    fprintf(fout, "%s %.2f\n", x->str, x->price);
}

int ITEMcompare (Item val1, Item val2) {
  Key k1, k2;
  k1 = KEYget(val1);
  k2 = KEYget(val2);
  return KEYcompare(k1, k2);
}

int KEYcompare(Key k1, Key k2) {
  if (k1<k2)
    return -1;
  if (k1==k2)
    return 0;
  return 1;
}

Key  KEYget(Item val) {
  return val->price;
}
int IDcompare(Item val1, Item val2) {
  return strcmp(val1->str, val2->str);
}

Item ITEMsetNull() {
  return NULL;
}

int ITEMcheckNull(Item x) {
  if (x == NULL)
    return 1;
  else
    return 0;
}
