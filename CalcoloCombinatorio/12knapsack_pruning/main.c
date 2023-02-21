#include <stdio.h>
#include <stdlib.h>
#include "Item.h"

void powerset(int pos, Item *items, int *sol, int k, int cap, int c_cap, int c_val, int *b_val, int *b_sol);

int main(void) {
  int i, k, cap, *sol, *b_sol, b_val=0;
  Item *items;

  printf("Input number of elements: ");
  scanf("%d", &k);

  items = malloc(k*sizeof(Item));
  sol = calloc(k, sizeof(int));
  b_sol = calloc(k, sizeof(int));

  printf("Input capacity of knapsack: ");
  scanf("%d", &cap);

  printf("Input elements: \n");
  for (i=0; i<k; i++)
    items[i] = ITEMscan();

  powerset(0, items, sol, k, cap, 0, 0, &b_val, b_sol);

  printf("The solution is set { ");
  for (i=0; i<k; i++)
    if (b_sol[i]!=0)
      ITEMshow(items[i]);
  printf("} \n");
  printf("best value = %d \n", b_val);

  return 1;

}

void powerset(int pos, Item *items, int *sol, int k, int cap, int c_cap, int c_val, int *b_val, int *b_sol) {
  int j;

  if (pos >= k) {
    if (c_val > *b_val) {
      for (j=0; j<k; j++)
        b_sol[j] = sol[j];
      *b_val = c_val;
    }
    return;
  }

  if ((c_cap + items[pos].size) > cap) {
    sol[pos] = 0;
    powerset(pos+1, items, sol, k, cap, c_cap, c_val, b_val, b_sol);
    return;
  }
  sol[pos] = 1;
  c_cap += items[pos].size;
  c_val += items[pos].value;
  powerset(pos+1, items, sol, k, cap, c_cap, c_val, b_val, b_sol);
  sol[pos] = 0;
  c_cap -= items[pos].size;
  c_val -= items[pos].value;
  powerset(pos+1, items, sol, k, cap, c_cap, c_val, b_val, b_sol);
}



