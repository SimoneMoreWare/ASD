#include<stdio.h>
#include <stdlib.h>

void Merge(int *A, int *B, int l, int q, int r);
void MergeSort(int *A, int *B, int l, int r);

int promising(int *val, int i,int part_sum,int rem_sum, int X);
void sumset(int pos, int *val, int *sol,  int part_sum, 
            int rem_sum, int X);

void main(void) {
  int i, k, rem_sum = 0;
  int *sol, *val, *tmp, X;

  printf("Inserisci il numero di elementi:  ");
  scanf("%d", &k);

  val = malloc(k * sizeof(int));
  tmp = malloc(k * sizeof(int));
  sol = malloc(k * sizeof(int));

  for (i = 0; i < k; i++)
      sol[i] = 0;

  printf("Inserisci gli elementi: \n");
  for (i = 0; i < k; i++) {
    printf("val[%d] = ", i);
    scanf("%d", &val[i]);
    rem_sum += val[i];
  }

  printf("Inserisci la somma: \n");
    scanf("%d", &X);

  MergeSort(val, tmp, 0, k-1);

  if (rem_sum < X)
    printf("Nessuna soluzione possibile \n");
  else {
    printf("La soluzione e':\n");
    sumset(0, val, sol, 0, rem_sum, X);
  }
  return;
}

int promising(int *val, int pos, int part_sum, int rem_sum, int X) {
  return(part_sum+rem_sum >= X )&& (part_sum+val[pos] <= X);
}


void sumset(int pos, int *val, int *sol, int part_sum, 
            int rem_sum, int X) {
  int j;

  if (part_sum == X) {
    printf("\n{\t");
    for(j = 0; j < pos; j++)
      if (sol[j])
        printf("%d\t", val[j]);
    printf("}\n");
    return;
  }

  if (promising(val, pos, part_sum, rem_sum, X)) {
    sol[pos] = 1;
    sumset(pos+1, val,sol,part_sum+val[pos],rem_sum-val[pos],X);
    sol[pos] = 0;
    sumset(pos+1, val, sol, part_sum, rem_sum-val[pos], X);
  }
}

