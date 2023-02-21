#include "Item.h"
#include "RecursiveSorting.h"
#define DBG 1

int min(int A, int B) {
  if (A < B)
    return A;
  return B;
}

void Merge(Item A[], Item B[], int l, int q, int r) {
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

void MergeSortR(Item A[], Item B[], int l, int r) {
  int q;
  if (r <= l)
    return;
  q = (l + r)/2;
  MergeSortR(A, B, l, q);
  MergeSortR(A, B, q+1, r);
  Merge(A, B, l, q, r);
}

void MergeSort(Item A[], Item B[], int N) {
  int l=0, r=N-1;
  MergeSortR(A, B, l, r);
}

void Swap( Item *v, int n1, int n2) {
  Item	temp;

  temp  = v[n1];
  v[n1] = v[n2];
  v[n2] = temp;
  return;
}


int partition ( Item A[], int l, int r ) {
  int i, j;
  Item x = A[r];
#if DBG
  printf("pivot = ");
  ITEMshow(x);
  printf("\n");
#endif
  i = l-1;
  j = r;
  for ( ; ; ) {
    while(ITEMlt(A[++i], x));
    while(ITEMgt(A[--j], x));
    if (i >= j)
      break;
    Swap(A, i, j);
  }
  Swap(A, i, r);
  return i;
}

void QuickSortR( Item A[], int l, int r ) {
  int q;
#if DBG
  int i;
#endif
  if (r <= l)
    return;
  q = partition(A, l, r);
#if DBG
  printf("partioning result\n");
  for (i=l; i <= r; i++)
    ITEMshow(A[i]);
  printf("\n");
#endif
  QuickSortR(A, l, q-1);
  QuickSortR(A, q+1, r);
  return;
}

void QuickSort(Item A[], int N) {
  int l=0, r=N-1;
  QuickSortR(A, l, r);
}
