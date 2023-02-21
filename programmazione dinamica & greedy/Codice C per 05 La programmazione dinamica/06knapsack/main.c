#include <stdio.h>
#include <stdlib.h>
#include "Item.h"
#define DBG 0

int KNAPmaxValR(Item *items, int N, int cap);
int KNAPmaxValDP(Item *items, int N, int cap);
void displaySol(Item *items, int N, int cap, int **maxval);

int main(void) {
  int i, N, cap;
  Item *items;

  printf("Input number of elements: ");
  scanf("%d", &N);

  items = malloc(N*sizeof(Item));
  printf("Input capacity of knapsack: ");
  scanf("%d", &cap);

  printf("Input elements: \n");
  for (i=0; i<N; i++)
    items[i] = ITEMscan();

  printf("Recursive approach: max value: %d\n", KNAPmaxValR(items, N-1, cap));
  printf("Dynamic Programming approach: max value: %d\n", KNAPmaxValDP(items, N, cap));
  return 1;

}

int max(int a, int b) {
  if (a >= b)
    return a;
  return b;
}

int maxValR(Item *items, int i, int j) {
  if ( (i < 0) || (j == 0))
    return 0;
  if (items[i].size >j)
    return maxValR(items, i-1, j);
  return max(maxValR(items, i-1, j), maxValR(items, i-1, j-items[i].size)+items[i].value);
}

int KNAPmaxValR(Item *items, int N, int cap) {
  return maxValR(items, N, cap);
}


int KNAPmaxValDP(Item *items, int N, int cap) {
  int i, j, **maxval;

  maxval = calloc((N+1), sizeof(int *));
  for (i = 0; i <= N; i++)
    maxval[i] = calloc((cap+1), sizeof(int));

  for (i=1; i<=N; i++)
    for (j=1; j <=cap; j++)
      if (items[i-1].size > j)
        maxval[i][j] = maxval[i-1][j];
      else
        maxval[i][j] = max(maxval[i-1][j], maxval[i-1][j-items[i-1].size] + items[i-1].value);
#if DBG
  printf("Maxval is: \n");
  for (i=0; i<=N; i++) {
    for (j=0; j <= cap; j++)
      printf("%d ", maxval[i][j]);
    printf("\n");
  }
#endif
  printf("Maximum booty is: \n");
  displaySol(items, N, cap, maxval);
  printf("\n");


  return maxval[N][cap];
}


void displaySol(Item *items, int N, int cap, int **maxval) {
  int i, j, *sol;
  sol = calloc(N, sizeof(int));
  j = cap;

  for (i=N; i>=1; i--)
    if (maxval[i][j] == maxval[i-1][j])
      sol[i-1] = 0;
    else  {
      sol[i-1] = 1;
      j-= items[i-1].size;
    }
  for (i=0; i<N; i++)
    if (sol[i])
      ITEMstore(items[i]);
}
