#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int min_diff = INT_MAX;

void perm(int pos, int *val, int *sol, int *mark, int *fin, int n);
void check(int *sol, int *fin, int n);

int main(void) {
  int i, n, k, tot, *val, *sol, *mark, *fin;

  printf("Inserisci n: ");
  scanf("%d", &n);
  val = malloc(n * sizeof(int));
  sol = malloc(n * sizeof(int));
  mark = malloc(n * sizeof(int));
  fin = malloc(n * sizeof(int));

  for (i = 0; i < n; i++) {
    sol[i]= -1;
    mark[i]= 0;
  }
  for (i = 0; i < n; i++) {
    printf("Inserisci elemento %d: ", i);
    scanf("%d", &val[i]);
  }

  perm(0, val, sol, mark, fin, n);

  printf("L'ordinamento che genera la differenza minima 
          pari a %d e' \n", min_diff);
  for (i = 0; i < n; i++)
    printf("%d ", fin[i]);
  printf("\n");

  return 0;
}

void perm(int pos, int *val, int *sol, int *mark, int *fin, int n) {
  int i;

  if (pos >= n) {
    check(sol, fin, n);
    return;
  }

  for (i=0; i<n; i++)
    if (mark[i] == 0) {
      mark[i] = 1;
      sol[pos] = val[i];
      perm(pos+1, val, sol, mark, fin, n);
      mark[i] = 0;
    }
  return;
}

void check(int *sol, int *fin, int n) {
  int i, saldo = 0, max_curr = 0, min_curr = INT_MAX, diff_curr;

  for (i = 0; i < n; i++) {
      saldo += sol[i];
      if (saldo > max_curr)
        max_curr = saldo;
      if (saldo < min_curr)
        min_curr = saldo;
  }
  diff_curr = max_curr - min_curr;
  if (diff_curr < min_diff) {
    min_diff = diff_curr;
    for (i = 0; i < n; i++)
      fin[i] = sol[i];
  }
  return;
}
