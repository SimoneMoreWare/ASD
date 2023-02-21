#include <stdio.h>
#include <stdlib.h>
#include "Item.h"

void powerset(int pos, Item *items, int *sol, int k, int cap, 
              int curr_cap, int curr_value, int *best_value, 
              int *best_sol);

int main(void) {
  int i, k, cap, *sol, *best_sol, best_value=0;
  Item *items;
  printf("Inserisci il numero di elementi: ");
  scanf("%d", &k);
  items = malloc(k * sizeof(Item));
  sol = malloc(k * sizeof(int));
  best_sol = malloc(k * sizeof(int));

  for (i = 0; i < k; i++) {
    sol[i] = 0;
    best_sol[i] = 0;
  }

  printf("Inserisci la capacita' dello zaino: ");
  scanf("%d", &cap);
  printf("Inserisci gli elementi: \n");
  for (i = 0; i < k; i++) items[i] = ITEMscan();

  powerset(0, items, sol, k, cap, 0, 0, &best_value, best_sol);
  printf("The solution is set { ");
  for (i = 0; i < k; i++)
    if (best_sol[i] != 0)
        ITEMshow(items[i]);
  printf("} \n");
  printf("best value = %d \n", best_value);
  return 1;
}

void powerset(int pos, Item *items, int *sol, int k, int cap, 
              int curr_cap, int curr_value, int *best_value, 
              int *best_sol) {
  int j;
  if (pos >= k) {
    if (curr_cap <= cap) {
        if (curr_value > *best_value) {
          for (j=0; j<k; j++) best_sol[j] = sol[j];
          *best_value = curr_value;
        }
    }
    return;
  }
  sol[pos] = 1;
  curr_cap += items[pos].size;
  curr_value += items[pos].value;
  powerset(pos+1, items, sol, k, cap, curr_cap, curr_value, 
           best_value, best_sol);
  sol[pos] = 0;
  curr_cap -= items[pos].size;
  curr_value -= items[pos].value;
  powerset(pos+1, items, sol, k, cap, curr_cap, curr_value, 
           best_value, best_sol);
}
