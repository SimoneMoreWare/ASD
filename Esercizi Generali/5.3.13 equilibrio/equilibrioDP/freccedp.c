#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define DBG 1

int *leggiFile(char *fn, int *N) {
  int i, *f;
  FILE *in = fopen(fn, "r");
  if (in == NULL)
    exit(-1);
  fscanf(in, "%d", N);
  f = calloc(*N, sizeof(int));
  if (f == NULL)
    exit(-1);
  for(i=0;i<*N;i++) {
    fscanf(in, "%d", &f[i]);
    if (f[i] != 0 && f[i] != 1) exit(-1);
  }
  fclose(in);
  return f;
}
int min(int x, int y){
  if (x <= y)
    return x;
  return y;
}

int contaCambi(int *frecce, int i, int j){
  int k, numCambi=0;
  for (k=i; k <= (i+j)/2; k++)
    if (frecce[k] == 1)
      numCambi++;
  for (k= ((i+j)/2+1); k <= j; k++)
    if (frecce[k] == 0)
      numCambi++;
  return numCambi;
}

void cambiaVerso(int *sol, int i, int j){
  int k;
  for (k=i; k <= (i+j)/2; k++)
    sol[k] = 0;
  for (k= ((i+j)/2+1); k <= j; k++)
    sol[k] = 1;
  return;
}

int minCostR(int *frecce, int i, int j, int minCost) {
  int k, cost;
  if (i == j-1)
    return contaCambi(frecce, i, j);
  for (k=i+1; k<j; k=k+2) {
    cost = min(minCostR(frecce, i, k, minCost) + minCostR(frecce, k+1, j, minCost), contaCambi(frecce, i,j));
    if (cost < minCost)
      minCost = cost;
  }
  return minCost;
}

int SolRic(int *frecce, int N) {
  return minCostR(frecce, 0, N-1, INT_MAX);
}

void displaySol(int **s, int *sol, int i, int j) {
  if (j == s[i/2][j/2]) {
    cambiaVerso(sol, i, j);
    return;
  }
  displaySol(s, sol, i, s[i/2][j/2]);
  displaySol(s, sol, s[i/2][j/2]+1, j);
  return;
}

int SolProgrDin(int *frecce, int N) {
  int l, i, j, k, q, **m, **s, *sol,res;


  m = calloc((N/2), sizeof(int *));
  s = calloc((N/2), sizeof(int *));
  sol = calloc(N, sizeof(int));

  for (i = 0; i < N/2; i++) {
    m[i] = calloc((N/2), sizeof(int));
    s[i] = calloc((N/2), sizeof(int));
  }

  for (l = 1; l <= N/2; l++) {
    for (i = 0; i < N/2- l +1; i++) {
      j = l + i -1;
      m[i][j] = contaCambi(frecce, 2*i, 2*i+2*l-1);
      s[i][j] = 2*i+2*l-1;
      for (k = 2*i+1; k < 2*i+2*l-1; k=k+2) {
        q = m[i][(k-1)/2] + m[(k+1)/2][j];
        if (q < m[i][j]) {
          m[i][j] = q;
          s[i][j] = k;
        }
      }
    }
  }

  displaySol(s, sol, 0, N-1);

  printf("Soluzione: ");
  for(i=0; i<N; i++)
    if(sol[i]==0)
      printf("%c", '>');
    else
      printf("%c", '<');
  printf("\n");
#if DBG
  printf("Problemi, costi minimi e scelte\n");
  for (l = 1; l <= N/2; l++)
    for (i = 0; i < N/2- l +1; i++) {
      j = l + i -1;
      printf("Problema (%d, %d), costo minimo m[%d][%d] = %d, scelta s[%d][%d] = %d\n", 2*i, 2*i+2*l-1, i, j, m[i][j], i, j, s[i][j]);
    }
#endif
  res = m[0][N/2-1];
  for (i = 0; i < N/2; i++) {
    free(s[i]);
    free(m[i]);
  }
  free(sol);
  free(s);
  free(m);
  return res;
}


int main() {
  int N = 0;
  int *frecce = leggiFile("frecce.txt", &N);

  printf("Soluzione ricorsiva: minimo numero di scambi %d\n", SolRic(frecce, N));
  printf("Soluzione con programmazione dinamica\n");
  printf("Minimo numero di scambi %d\n", SolProgrDin(frecce, N));
  free(frecce);
  return 0;
}

