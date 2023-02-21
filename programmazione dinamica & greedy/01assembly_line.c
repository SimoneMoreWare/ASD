#include <stdio.h>
#include <stdlib.h>

int assembly_lineR(int **a, int **t, int *e, int *x, int n);
int assembly_lineDP(int **a, int **t, int *e, int *x, int **f, int **l, int n);
void displaySol(int **l, int i, int n);

int main(void) {
  int n, i, j, **a, e[2], x[2], **t, **f, **l;

  printf("Input number of assembly stations: ");
  scanf("%d", &n);

  printf("Input entry time for line0: ");
  scanf("%d", &e[0]);
  printf("Input entry time for line1: ");
  scanf("%d", &e[1]);

  printf("Input exit time for line0: ");
  scanf("%d", &x[0]);
  printf("Input exit time for line1: ");
  scanf("%d", &x[1]);


  a = malloc(2*sizeof(int *));
  for (i=0; i<2; i++)
    a[i] = malloc(n*sizeof(int));

  t = malloc(2*sizeof(int *));
  for (i=0; i<2; i++)
    t[i] = malloc((n-1)*sizeof(int));


  f = malloc(2*sizeof(int *));
  for (i=0; i<2; i++)
    f[i] = malloc(n*sizeof(int));

  l = malloc(2*sizeof(int *));
  for (i=0; i<2; i++)
    l[i] = malloc((n+1)*sizeof(int));

  printf("Input station processing time: \n");
  for (i=0; i<2; i++)
    for (j=0; j<n; j++) {
      printf("a[%d][%d] = ", i, j);
      scanf("%d", &a[i][j]);
    }

  printf("Input tranfer time: \n");
  for (i=0; i<2; i++)
    for (j=0; j<n-1; j++) {
      printf("t[%d][%d] = ", i, j);
      scanf("%d", &t[i][j]);
    }

  printf("Minimum assembly time (recursive algorithm): %d\n",assembly_lineR(a, t, e, x, n-1));
  printf("Minimum assembly time (dynamic programming algorithm): %d\n",assembly_lineDP(a, t, e, x, f, l, n));
  displaySol(l, 0, n);

  return 1;
}

int min (int a, int b) {
  if (a <= b)
    return a;
  else
    return b;
}

int minCostR(int **a, int **t, int *e, int *x, int j, int i) {
  int ris;

  if (j==0)
    return e[i] + a[i][j];
  ris = min(minCostR(a, t, e, x, j-1, i) + a[i][j], minCostR(a, t, e, x, j-1, (i+1)%2) + t[(i+1)%2][j-1] + a[i][j]);
  return ris;
 }

int assembly_lineR(int **a, int **t, int *e, int *x, int j){
  return min(minCostR(a,t, e, x, j, 0) + x[0], minCostR(a,t, e, x, j, 1) + x[1]);
}

int assembly_lineDP(int **a, int **t, int *e, int *x, int **f, int **l, int n){
  int j, res;

  f[0][0] = e[0] + a[0][0];
  f[1][0] = e[1] + a[1][0];

  for (j=1; j<n; j++) {
    if (f[0][j-1] + a[0][j] <= f[1][j-1] + t[1][j-1] + a[0][j]) {
      f[0][j] = f[0][j-1] + a[0][j];
      l[0][j] = 0;
    }
    else  {
      f[0][j] = f[1][j-1] + t[1][j-1] + a[0][j];
      l[0][j] = 1;
     }

    if (f[1][j-1] + a[1][j] <= f[0][j-1] + t[0][j-1] + a[1][j]) {
      f[1][j] = f[1][j-1] + a[1][j];
      l[1][j] = 1;
     }
    else  {
      f[1][j] = f[0][j-1] + t[0][j-1] + a[1][j];
      l[1][j] = 0;
     }
   }

  if (f[0][n-1] + x[0] <= f[1][n-1] + x[1]) {
     res = f[0][n-1] + x[0];
     l[0][n] = 0;
     l[1][n] = 0;
  }
  else {
     res = f[1][n-1] + x[1];
     l[0][n] = 1;
     l[1][n] = 1;
  }
  return res;
}


void displaySol(int **l, int i, int n) {
  if (n==0)
    return;
  displaySol(l, l[i][n-1], n-1);
  printf("line %d station %d\n", i, n-1);
}



