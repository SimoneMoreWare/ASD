#include<stdlib.h>
#include<string.h>
#include<stdio.h>



int check(int S[][10], int *sol, int k) {
  int *occ, i, j, ok=1;
  occ = calloc(9+1, sizeof(int));
  if (occ == NULL)
    exit(-1);
  for (i=0; i<k; i++) {
    j=0;
    while(S[sol[i]][j] && j<10)
      occ[S[sol[i]][j++]] = 1;
  }
  for (i=1; i<=9 && ok; i++)
    if (!occ[i])
      ok = 0;
  free(occ);
  return ok;
}

int comb(int pos, int S[][10], int *sol, int n, int k,  int start) {
  int i;
  if (pos >= k) {
    if (check(S, sol, k))
      return 1;
    else
      return 0;
  }

  for (i=start; i<n; i++) {
    sol[pos] = start;
    if (comb(pos+1, S, sol, n, k, i+1))
      return 1;
  }
  return 0;
}

void cover(int S[][10], int n, int k) {
  int i, *sol;
  if (k <= 0) {
    printf("Impossibile effettuare copertura (k=%d)\n", k);
    return;
  }
  if (k > n) {
    printf("Impossibile effettuare copertura (k>n)\n");
    return;
  }
  sol = calloc(k, sizeof(int));
  if (sol == NULL)
    exit(-1);
  if (comb(0, S, sol, n, k, 0)) {
    printf("Insiemi scelti: ");
    for (i=0; i<k; i++)
      printf(" %d", sol[i]);
    printf("\n");
  } else
      printf("Impossibile effettuare copertura con k=%d\n", k);
  free(sol);
}

int main() {
  int subsets[][10] = {{1,2,3,0}, {2,3,7,0}, {7,8,9,0}, {3,4,0}, {4,5,6,0}};
  int n = 5, k;
  printf("Input k: ");
  scanf("%d", &k);
  cover(subsets, n, k);
  return 0;
}
