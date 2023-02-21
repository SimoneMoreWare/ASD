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
    else if (ITEMgt(A[i], A[j]) || ITEMeq(A[i], A[j])  )
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


float knapsack(int n, Item *objects, float cap) {
  float stolen = 0.0, res = cap;
  int i;

  for (i=0; i<n && (KEYgetW(objects[i]) <= res);i++) {
    KEYsetF(&objects[i], 1.0);
    stolen = stolen + KEYgetV(objects[i]);
    res = res - objects[i].weight;
  }

  KEYsetF(&objects[i], res/KEYgetW(objects[i]));
  stolen = stolen + KEYgetF(objects[i])*KEYgetV(objects[i]);

  return stolen;

}

int main() {
  int n, i;
  float cap, stolen=0.0;
  Item *objects;

  printf ("No. of objects: ");
  scanf ("%d", &n);

  objects = calloc(n,sizeof(Item));

  printf("Input objects: \n");
  for (i=0; i<n; i++)
    objects[i] = ITEMscan();

  printf ("Capacity of knapsack: ");
  scanf ("%f", &cap);


  MergeSort(objects, n);

  stolen = knapsack(n, objects, cap);

  printf("Results: \n");
  for(i = 0; i < n; i++)
    ITEMstore(objects[i]);

  printf("Total amount stolen: %.2f \n", stolen);

  return 0;
}
