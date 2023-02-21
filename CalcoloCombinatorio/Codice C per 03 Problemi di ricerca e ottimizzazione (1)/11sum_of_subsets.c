#include<stdio.h>
#include <stdlib.h>

void MergeSort(int *A, int N);

int promising(int *val, int i,int p, int r, int X);
void sumset(int pos, int *val, int *sol,  int p, int r, int X);

int main(void) {
  int i, k, total=0;
  int *sol, *val, X;

  printf("Enter number of elements:  ");
  scanf("%d",&k);

  val = malloc(k*sizeof(int));
  sol = calloc(k, sizeof(int));

  printf("Input elements: \n");
  for (i=0; i<k; i++) {
    printf("val[%d] = ", i);
    scanf("%d", &val[i]);
    total+=val[i];
  }

  printf("Input sum: ");
  scanf("%d", &X);

  MergeSort(val, k);

  if((total < X))
    printf("No solution possible \n");
  else {
    printf("The solution is:\n");
    sumset(0, val, sol, 0, total, X);
  }

  free(val);
  free(sol);

  return 0;
}

int promising(int *val, int pos, int p, int r, int X) {
  return(p+r>=X)&&(p+val[pos]<=X);
}

void sumset(int pos, int *val, int *sol, int p, int r, int X) {
  int j;

  if (p==X) {
    printf("\n{\t");
    for(j=0;j<pos;j++)
      if(sol[j])
        printf("%d\t",val[j]);
      printf("}\n");
    return;
  }

  if (promising(val,pos,p,r,X)) {
    sol[pos]=1;
    sumset(pos+1, val, sol, p+val[pos], r-val[pos], X);
    sol[pos]=0;
    sumset(pos+1, val, sol, p, r-val[pos], X);
  }
}

void Merge(int *A, int *B, int l, int q, int r) {
  int i, j, k;
  i = l;
  j = q+1;
  for(k = l; k <= r; k++)
    if (i > q)
      B[k] = A[j++];
    else if (j > r)
      B[k] = A[i++];
    else if ( (A[i] < A[j]) || (A[i] == A[j])  )
      B[k] = A[i++];
    else
      B[k] = A[j++];
  for ( k = l; k <= r; k++ )
    A[k] = B[k];
  return;
}
void MergeSortR(int *A, int *B, int l, int r) {
  int q;
  if (r <= l)
    return;
  q = (l + r)/2;
  MergeSortR(A, B, l, q);
  MergeSortR(A, B, q+1, r);
  Merge(A, B, l, q, r);
}

void MergeSort(int *A, int N) {
  int l=0, r=N-1;
  int *B = (int *)malloc(N*sizeof(int));
  if (B == NULL) {
    printf("Memory allocation error\n");
    exit(1);
  }
  MergeSortR(A, B, l, r);
}
