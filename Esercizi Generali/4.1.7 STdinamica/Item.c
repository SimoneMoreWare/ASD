#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "Item.h"

struct item {
  char key[MAXK];
  char *name;
  char *surname;
  char *data;
};

Item ITEMnew() {
  Item val=(Item) calloc(1,sizeof(struct item));
  if (val==NULL)
    return NULL;
  return val;
}

Item ITEMscan(FILE *fin) {
  Item val;
  if (fin == NULL)
    return NULL;
  val = ITEMnew();
  if (val != NULL) {
    val->name = calloc(MAXC, sizeof(char));
    val->surname = calloc(MAXC, sizeof(char));
    val->data = calloc(MAXK, sizeof(char));
    fscanf(fin, "%s %s %s %s", val->key, val->name, val->surname, val->data);
  }
  return val;
}

void ITEMstore(FILE *fout, Item val) {
  if (fout == NULL || val == NULL)
    return;
  fprintf(stdout, "%s %s %s %s\n", val->key, val->name, val->surname, val->data);
}

int ITEMcompare (Item val1, Item val2) {
  return KEYcompare(val1->key, val2->key);
}

void ITEMfree(Item val) {
  if (val == NULL)
    return;
  free(val->name);
  free(val->surname);
  free(val->data);
  free(val);
}

int  KEYcompare(Key k1, Key k2) {
  return strcmp(k1, k2);
}

Key  KEYscan() {
  Key k = calloc(MAXK, sizeof(*k));
  fscanf(stdin, "%s", k);
  return k;
}

void KEYfree(Key k) {
  if (k == NULL)
    return;
  free(k);
}

Key  KEYget(Item val){
  return val->key;
}
