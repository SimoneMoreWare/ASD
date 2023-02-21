#include <stdio.h>
#include <stdlib.h>
#include <limits.h>


int minCostR(int *p, int i, int j, int minCost);
int matrix_chainR(int *p, int n);
int matrix_chainDP(int *p, int n);
int matrix_chainM(int *p, int n);
int lookup(int *p, int i, int j, int **m);
void displaySol(int **s, int i, int j);

int main () {
  int i, n, *p ;

  printf("Input n: \n");
  scanf("%d", &n);

  p = malloc((n+1)*sizeof(int));

  printf("Input vettore p delle dimensioni:\n");
  for (i=0; i<=n; i++) {
    printf("p[%d] = ", i);
    scanf("%d", &p[i]);
  }

  printf("algoritmo ricorsivo: il costo minimo e' %d\n", matrix_chainR(p, n));
  printf("algoritmo di programmazione dinamica: soluzione\n");
  printf("costo minimo: %d\n", matrix_chainDP(p, n));
  printf("algoritmo con memoization: il costo minimo e' %d\n", matrix_chainM(p, n));

  return 0;

}

int minCostR(int *p, int i, int j, int minCost) {
  int k, cost;
  if (i == j)
    return 0;
  for (k=i; k<j; k++) {
    cost = minCostR(p, i, k, minCost) + minCostR(p, k+1, j, minCost) + p[i-1]*p[k]*p[j];
    if (cost < minCost)
      minCost = cost;
  }
  return minCost;
}

int matrix_chainR(int *p, int n) {
  return minCostR(p, 1, n, INT_MAX);
}

int matrix_chainDP(int *p, int n) {
  int i, l, j, k, q, **m, **s;

  m = calloc((n+1), sizeof(int *));
  s = calloc((n+1), sizeof(int *));

  for (i = 0; i <= n; i++) {
    m[i] = calloc((n+1), sizeof(int));
    s[i] = calloc((n+1), sizeof(int));
  }

  for (l = 2; l <= n; l++)
    for (i = 1; i <= n-l+1; i++) {
      j = i+l-1;
      m[i][j] = INT_MAX;
      for (k = i; k <= j-1; k++) {
        q = m[i][k] + m[k+1][j] + p[i-1]*p[k]*p[j];
        if (q < m[i][j]) {
          m[i][j] = q;
          s[i][j] = k;
        }
      }
      printf("m[%d][%d] = %d\n", i, j, m[i][j]);
    }
    displaySol(s, 1, n);
    printf("\n");
  return m[1][n];
}

void displaySol(int **s, int i, int j) {
  if (j <= i) {
    printf("A%d", i);
    return;
  }
  printf("(");
  displaySol(s, i, s[i][j]);
  printf(") x (");
  displaySol(s, s[i][j]+1, j);
  printf(")");
  return;
}

int matrix_chainM(int *p, int n) {
  int i, j, **m;
  m = malloc((n+1) * sizeof(int *));
  for (i = 0; i <= n; i++)
    m[i] = malloc((n+1)*sizeof(int));

  for (i = 0; i <= n; i++)
    for (j = 0; j <= n; j++)
      m[i][j] = INT_MAX;

  return lookup(p, 1, n, m);
}

int lookup(int *p, int i, int j, int **m) {
  int k, q;
  if (m[i][j] < INT_MAX)
    return m[i][j];
  if (i==j)
    m[i][j] = 0;
  else
    for (k= i; k <j; k++) {
      q = lookup(p, i, k, m) + lookup(p, k+1, j, m) + p[i-1]*p[k]*p[j];
      if (q < m[i][j])
        m[i][j] = q;
    }
  return m[i][j];
}
