#include<stdlib.h>
#include<string.h>
#include<stdio.h>

int **leggiFile(FILE *in, int *n, int *m) {
  int i, j, **mat;
  fscanf(in, "%d %d", n, m);
  mat = calloc(*n, sizeof(int *));

  for (i=0; i<*n; i++) {
    mat[i] = calloc(*m, sizeof(int));
    for (j=0; j<*m; j++)
      fscanf(in, "%d", &mat[i][j]);
  }
  return mat;
}

int verifica(int **inter, int m, int k, int *sol) {
  int i, j, ok = 1, *lampadine;
  lampadine = calloc(m, sizeof(int));

  for (j=0; j<m && ok; j++){
    for (i=0; i<k; i++)
      lampadine[j] ^= inter[sol[i]][j];
    if (lampadine[j]==0)
      ok = 0;
  }
  free(lampadine);
  return ok;
}
/*
int verifica(int **inter, int m, int k, int *sol) {
  int i, j, ok = 1, *lampadine;
  lampadine = calloc(m, sizeof(int));

  for(j=0; j<m && ok; j++) {
    for (i=0; i<k; i++)
      lampadine[j] += inter[sol[i]][j];
    if (lampadine[j]%2 ==0)
      ok = 0;
  }
  free(lampadine);
  return ok;
}
*/

int powerset_comb(int pos, int *sol, int n, int k, int start, int **inter,  int m) {

  int i;
  if (pos >= k) {
    if (verifica(inter, m, k, sol)) {
      printf("Insieme minimo di interruttori per accendere  tutte le lampadine:\n");
      for (i=0; i < k; i++)
        printf("%d ", sol[i]);
      printf("\n");
      return 1;
    }
    return 0;
  }

  for (i = start; i < n; i++) {
    sol[pos] = i;
    if (powerset_comb(pos+1, sol, n, k, i+1, inter, m))
      return 1;
  }
  return 0;
}

int main(void) {
  int n, m, k, i, trovato=0, *sol, *mark, **inter;
  FILE *in = fopen("switches.txt", "r");

  inter = leggiFile(in, &n, &m);

  sol = calloc(n, sizeof(int));
  mark = calloc(n, sizeof(int));

  printf("Powerset mediante combinazioni semplici\n\n");

  for (k=1; k <= n && trovato==0; k++) {
    if(powerset_comb(0, sol, n, k, 0, inter, m))
      trovato = 1;
  }
  free(sol);
  free(mark);
  for (i=0; i < n; i++)
    free(inter[i]);
  free(inter);
  return 0;
}
