#include <stdio.h>
#include <stdlib.h>
#define MAX 10

void powerset(int pos, int *val, int *sol, int k, int X);
int check(int *sol, int *val, int X, int k);

int main(void) {
  int i, k, X, *val, *sol;

  printf("Inserisci il numero di elementi: ");
  scanf("%d", &k);

  val = malloc(k * sizeof(int));
  sol = malloc(k * sizeof(int));

  for (i = 0; i < k; i++)
      sol[i] = 0;

  printf("Inserisci gli elementi: \n");
  for (i = 0; i < k; i++) {
    printf("val[%d] = ", i);
    scanf("%d", &val[i]);
  }

  printf("Inserisci la somma: \n");
    scanf("%d", &X);

  printf("L'insieme delle parti di  {");
  for(i = 0; i < k; i++)
    printf(" %d ", val[i]);
  printf(" } e' \n");

  powerset(0, val, sol, k, X);

  return;
}

void powerset(int pos, int *val, int *sol, int k, int X) {
  int j, out;

  if (pos >= k) {
    out = check(sol, val, X, k);
    if (out == 1) {
      printf("{ \t");
      for (j = k-1; j >= 0; j--)
        if (sol[j] != 0)
          printf("%d \t", val[k-j-1]);
        printf("} \n");
    }
    return;
  }

  sol[pos] = 0;
  powerset(pos+1, val, sol, k, X);
  sol[pos] = 1;
  powerset(pos+1, val, sol, k, X);
}

int check(int *sol, int *val, int X, int k) {
  int j, tot = 0;
  for (j = k-1; j >= 0; j--)
    if (sol[j] != 0)
      tot += val[k-j-1];
  if (tot == X)
    return 1;
  else
    return 0;
}
