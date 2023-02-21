#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Item.h"
#include "ST.h"

void loadCustomers(FILE *fin, ST *customers, ST *categories);
void loadAccesses(FILE *fin, ST customers, ST categories);
void storeResults(FILE *fout, ST customers, ST categories);

int main(int argc, char *argv[]) {
  FILE *fin;
  ST customers = NULL;
  ST categories = NULL;

  if (argc != 3) {
    printf("Use: %s customerInFile accessInFile ", argv[0]);
    exit(-1);
  }

  fin = fopen(argv[1], "r");
  if (fin == NULL)
    exit(-1);
  loadCustomers(fin, &customers, &categories);
  if (customers == NULL || categories == NULL)
    exit(-1);
  fclose(fin);

  fin = fopen(argv[2], "r");
  if (fin == NULL)
    exit(-1);
  loadAccesses(fin, customers, categories);
  fclose(fin);

  printf("Final information by customer:\n");
  STlistByCust(stdout, customers);

  printf("\nFinal information by category:\n");
  STlistByCat(stdout, categories);
  STfree(categories);
  STfree(customers);
  

  return 0;
}

void loadCustomers(FILE *fin, ST *customers, ST *categories) {
  Item customer;
  Item category, tmp;

  *customers = STinit(20);
  *categories = STinit(20);
  if (*customers == NULL || *categories == NULL) return;
  customer = ITEMscan(fin);
  while (!ITEMcheckNullCust(customer)) {
    STinsertByCust(*customers, customer);
    category = STsearchByCat(*categories, customer.cat);
    if (ITEMcheckNullCat(category)) {
      category = ITEMsetCat(KEYgetCat(&customer));
      ITEMinsertInList(&category, customer);
      STinsertByCat(*categories, category);
    }
    else {
      ITEMinsertInList(&category, customer);
      tmp = category;
      STdeleteByCat(*categories, category);
      STinsertByCat(*categories, tmp);
    }
    customer = ITEMscan(fin);
  }
  return;
}

void loadAccesses(FILE *fin, ST customers, ST categories) {
  Item customer, category, tmp;
  int kb, sec;
  char id[MAXC];

  while (fscanf(fin, "%s %d %d", id, &kb, &sec) == 3) {
    customer = STsearchByCust(customers, id);
    if (ITEMcheckNullCust(customer)) {
      printf("Error: unrecognized customer %s\n", id);
      continue;
    }
    customer.numAccess++;
    customer.totKB += kb;
    customer.totTime += sec;
    tmp = customer;

    category = STsearchByCat(categories, customer.cat);
    STdeleteByCust(customers, customer);
    STinsertByCust(customers, tmp);

    if (ITEMcheckNullCat(category)) {
      printf("Error: unrecognized category\n");
      continue;
    }
    category.totKB += kb;
    category.totTime += sec;
    tmp = category;
    STdeleteByCat(categories, category);
    STinsertByCat(categories, tmp);
  }
  return;
}
