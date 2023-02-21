#include <stdio.h>
#include <stdlib.h>
#include "Item.h"

void Merge(Item *A, Item *B, int l, int q, int r) {
  int i, j, k;
  i = l;
  j = q+1;
  for(k = l; k <= r; k++)
    if (i > q)
      B[k] = A[j++];
    else if (j > r)
      B[k] = A[i++];
    else if (ITEMlt(A[i], A[j]) || ITEMeq(A[i], A[j])  )
      B[k] = A[i++];
    else
      B[k] = A[j++];
  for ( k = l; k <= r; k++ )
    A[k] = B[k];
  return;
}

void MergeSortR(Item *A, Item *B, int l, int r) {
  int q;
  if (r <= l)
    return;
  q = (l + r)/2;
  MergeSortR(A, B, l, q);
  MergeSortR(A, B, q+1, r);
  Merge(A, B, l, q, r);
}

void MergeSort(Item *A, int N) {
  int l=0, r=N-1;
  Item *B = (Item *)malloc(N*sizeof(Item));
  if (B == NULL) {
    printf("Memory allocation error\n");
    exit(1);
  }
  MergeSortR(A, B, l, r);
}

void select(Item *act, int n) {
  int i, stop;

  KEYsetSel(&act[0]);
  stop = KEYgetStop(act[0]);

  for (i=1; i<n; i++)
    if (KEYgetStart(act[i]) >= stop) {
      KEYsetSel(&act[i]);
      stop = KEYgetStop(act[i]);
    }
}

int main() {
  int n, i;
  Item *act;

  printf("No. of activities: ");
  scanf("%d", &n);

  act = calloc(n,sizeof(Item));

  printf("Input activities: \n");
  for (i=0; i<n; i++)
    act[i] = ITEMscan();

  MergeSort(act, n);

  select(act, n);

  printf("Selected activities: \n");
  for (i=0; i<n; i++)
    if (KEYgetSel(act[i])==1)
      ITEMstore(act[i]);

  return 0;
}
