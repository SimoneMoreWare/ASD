#include "Item.h"
#include "RecursiveSorting.h"


int min(int A, int B) {
   if (A < B)
      return A;
   else
      return B;
}

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

void BottomUpMergeSort(Item *A, int N) {
  int i, m, l=0, r=N-1;
  Item *B = (Item *)malloc(N*sizeof(Item));
  if (B == NULL) {
    printf("Memory allocation error\n");
    exit(1);
  }

  for (m = 1; m <= r - l; m = m + m) {
    for (i = l; i <= r-m ; i += m + m)
      Merge(A, B, i, i+m-1, min(i+m+m-1,r));
  }
  return;
}

void Swap( Item *v, int n1, int n2) {
  Item	temp;

  temp  = v[n1];
  v[n1] = v[n2];
  v[n2] = temp;
  return;
}


int partition ( Item *A, int l, int r ) {
  int i, j;
  Item x = A[r];
  i = l-1;
  j = r;
  for ( ; ; ) {
    while(ITEMlt(A[++i], x));
    while(ITEMgt(A[--j], x))
    if (j == l)
      break;
    if (i >= j)
      break;
    Swap(A, i, j);
  }
  Swap(A, i, r);
  return i;
}

void QuickSortR( Item *A, int l, int r ) {
  int q;
  if (r <= l)
    return;
  q = partition(A, l, r);
  QuickSortR(A, l, q-1);
  QuickSortR(A, q+1, r);
  return;
}

void QuickSort(Item *A, int N) {
  int l=0, r=N-1;
  QuickSortR(A, l, r);
}
