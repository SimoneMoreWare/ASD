#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Item.h"


static listLink NEW(Key k, listLink next) {
  listLink x;
  x = malloc(sizeof(*x));
  if (x == NULL)
    exit(-1);
  strcpy(x->surname, k);
  x->next = next;
  return x;
}

Item ITEMscan(FILE *fin) {
  Item customer;
  char buf[MAXC];

  fscanf(fin, "%s", buf);
  strcpy(customer.id, buf);
  fscanf(fin, "%s", buf);
  strcpy(customer.name, buf);
  fscanf(fin, "%s", buf);
  strcpy(customer.surname, buf);
  fscanf(fin, "%s", buf);
  strcpy(customer.cat, buf);
  customer.numAccess = customer.totKB = customer.totTime = 0;
  customer.customerList = NULL;
  return customer;
}

Item ITEMsetNull() {
  Item val = {"none", "", "", 0, 0, 0, "none", NULL};
  return val;
}


Item ITEMsetCat(Key k) {
  Item val;
  strcpy(val.id,"");
  strcpy(val.surname, "");
  strcpy(val.name, "");
  val.numAccess= 0;
  val.totKB = 0;
  val.totTime = 0;
  strcpy(val.cat, k);
  val.customerList = NULL;
  return val;
}

int  ITEMcheckNullCust(Item val){
  if (strcmp(val.id, "none")==0)
    return 1;
  return 0;
}

int  ITEMcheckNullCat(Item val){
  if (strcmp(val.cat,"none")==0)
    return 1;
  return 0;
}

void ITEMstoreCust(FILE *fout, Item val){
    fprintf(fout, "%s %s:\n category: %s no. of accesses: %d, %d KB, %d sec\n", val.surname, val.name, val.cat, val.numAccess, val.totKB, val.totTime);
}

void ITEMstoreCat(FILE *fout, Item val){
    fprintf(fout, "Category %s\n  traffic = %d KB, time = %d sec \n", val.cat, val.totKB, val.totTime);
}

void ITEMstoreCustByCat(FILE *fout, Key k){
    fprintf(fout, "  %s ", k);
}

Key KEYgetId(Item *pval) {
  return pval->id;
}

Key KEYgetSurname(Item *pval) {
  return pval->surname;
}

Key KEYgetCat(Item *pval) {
  return pval->cat;
}

int KEYcompare(Key k1, Key k2) {
  return strcmp(k1, k2);
}

void ITEMfree(Item val1) {
  if(val1.customerList != NULL)
    CustomerListfree(val1.customerList);
}

void CustomerListfree(listLink customerList) {
  if(customerList != NULL)
    CustomerListfree(customerList->next);
  free(customerList);
}

void ITEMinsertInList(Item *val1, Item val2) {
  (*val1).customerList = NEW(KEYgetSurname(&val2), (*val1).customerList);
}

void ITEMcategoryListCustomers(Item category) {
  listLink t;
  for (t=category.customerList; t != NULL; t = t->next)
    ITEMstoreCustByCat(stdout,t->surname);
  printf("\n");
}
