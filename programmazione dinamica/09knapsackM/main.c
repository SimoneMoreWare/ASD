#include <stdio.h>
#include <stdlib.h>
#include "Item.h"

int KNAPmaxValR(Item *items, int N, int cap);
int KNAPmaxValM(Item *items, int N, int cap, int *maxKnown);

int main(void) {
  int i, N, cap, *maxKnown;
  Item *items;

  printf("Input number of elements: ");
  scanf("%d", &N);

  items = malloc(N*sizeof(Item));
  printf("Input capacity of knapsack: ");
  scanf("%d", &cap);

  printf("Input elements: \n");
  for (i=0; i<N; i++)
    items[i] = ITEMscan();

  maxKnown = malloc((cap+1)*sizeof(int));
  for (i=0; i<=cap; i++)
    maxKnown[i]= -1;

  printf("Max value (recursive algorithm): %d\n", KNAPmaxValR(items, N, cap));
  printf("Max value (memoization): %d\n", KNAPmaxValM(items, N, cap, maxKnown));
  return 1;

}

int KNAPmaxValR(Item *items, int N, int cap) {
  int i, space, max, t;
  for (i = 0, max = 0; i < N; i++)
    if ((space = cap-items[i].size) >= 0)
      if ((t = KNAPmaxValR(items, N, space) + items[i].value)> max)
        max = t;
  return max;
}

int KNAPmaxValM(Item *items, int N, int cap, int *maxKnown) {
  int i, space, max, t;
  if (maxKnown[cap] != -1)
    return maxKnown[cap];
  for (i=0, max=0; i < N; i++)
    if ((space = cap-items[i].size) >= 0)
      if ((t = KNAPmaxValM(items, N, space, maxKnown) + items[i].value) > max)
        max = t;
  maxKnown[cap] = max;
  return max;
}

