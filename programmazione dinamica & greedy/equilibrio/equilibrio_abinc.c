#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

/* Soluzioni calcolo combinatorio - esercitazione 6 - Le soluzioni con programmazione dinamica sono piu' in basso */
void powerset1r(int pos, int *frecce, int *sol, int n,
	      int curr_num, int *best_sol, int *best_num) {
  int i, check_ok;
  if (pos == n) {
    check_ok = check(frecce, sol, n);
    if (curr_num < *best_num && check_ok) {
      *best_num = curr_num;
      for (i=0;i<n;i++)
	best_sol[i] = sol[i];
    }
    return;
  }
  sol[pos] = 0;
  powerset1r(pos+1,frecce,sol,n,curr_num,best_sol,best_num);
  if (curr_num < *best_num) {
    sol[pos] = 1;
    powerset1r(pos+1,frecce,sol,n,curr_num+1,best_sol,best_num);
  }
  return;
}

int powerset1(int *frecce, int *best_sol, int n) {
  int *sol = (int *) malloc(sizeof(int)*n);
  int best_num = n;
  
  powerset1r(0, frecce, sol, n, 0, best_sol, &best_num);

  free(sol);
  
  if (best_num >= n) /* se n fosse dispari non esiste soluzione */
    return -1;
  return best_num;
  
}

int powerset2r(int pos, int *frecce, int *sol, int n, int k, int start) {
  int i, check_ok;
  if (pos >= k) {
    
    int *flip = (int *) calloc(n, sizeof(int));
    
    for (i=0; i<k; i++)
      flip[sol[i]] = 1;

    check_ok = check(frecce, flip, n);

    free(flip);
    
    if (check_ok) {
      return 1;
    }
    
    return 0;
    
    }
  
  for (i=start; i<n; i++) {
    sol[pos] = i;
    if(powerset2r(pos+1, frecce, sol, n, k, i+1)) {
      return 1;
    }
  }
  return 0;
}
  
int powerset2(int *frecce, int *best_sol, int n) {

  int *sol = (int *) malloc(sizeof(int)*n);
  
  int k = 0;
  for (k = 0; k <= n; k++) {

    if(powerset2r(0, frecce, sol, n, k, 0)) {
      int i;
      for (i = 0; i < n; i++)
	best_sol[i] = 0;
      for (i = 0; i < k; i++)
	best_sol[sol[i]] = 1;
      free(sol);
      return k;
    }
  }
  free(sol);
  return -1; /* Se n fosse dispari non esiste soluzione */
}

int check(int *f, int *sol, int n) {
  int *tmp = calloc(n, sizeof(int)), i, dx, sx;
  for (i=0; i<n; i++)
    tmp[i] = f[i] ^ sol [i];
  if (tmp[0] == 1 || tmp[n-1] == 0) {
    free(tmp);
    return 0;
  }
  i=0;
  while (i<n) {
    dx=0;
    sx=0;
    while (tmp[i]==0 && i<n ) {
      dx++;
      i++;
    }
    while (tmp[i]==1 && i<n ) {
      sx++;
      i++;
    }
    if ((dx-sx) !=0){
      free(tmp);
      return 0;
    }
  }
  free(tmp);
  return 1;

}

/* Esercitazione 9
Le sequenze sono indicizzate da [a, b], con a e b entrambi inclusi
*/

void cambiaVerso(int *sol, int i, int j);
int contaCambi(int *frecce, int i, int j);
void displaySol(int **s, int *sol, int i, int j);
int minCostR1(int *frecce, int **s, int i, int j, int minCost, int *nCalls);
int minCostR2(int *frecce, int **s, int **m, int i, int j, int minCost, int *nCalls);

int SolRic1(int *frecce, int *best_sol, int n) {
  int **s, res, i;
  int nCalls = 0;
  
  s = calloc((n/2), sizeof(int *));
  for (i = 0; i < n/2; i++) {
    s[i] = calloc((n/2), sizeof(int));
  }
  res = minCostR1(frecce, s, 0, n-1, INT_MAX, &nCalls);
  printf ("Soluzione ricorsiva: %d chiamate\n", nCalls);
  displaySol(s, best_sol, 0, n-1);
  for (i = 0; i < n/2; i++) {
    free(s[i]);
  }
  free(s);
  return res;
}

int minCostR1(int *frecce, int **s, int i, int j, int minCost, int *nCalls) {
  int k, cost;
  (*nCalls)++;
  if (i == j-1) {
    s[i/2][j/2] = j;
    return contaCambi(frecce, i, j);
  }
  minCost = contaCambi(frecce, i, j);
  s[i/2][j/2] = j;
  for (k=i+1; k<j; k=k+2) {
    cost = minCostR1(frecce, s, i, k, minCost, nCalls) + minCostR1(frecce, s, k+1, j, minCost, nCalls);
    if (cost < minCost) {
      minCost = cost;
      s[i/2][j/2] = k;
    }
  }
  return minCost;
}



int SolDinMemo(int *frecce, int *best_sol, int n) {
  int **s, res, i,j;
  int **m;
  int nCalls = 0;
  
  s = calloc((n/2), sizeof(int *));
  for (i = 0; i < n/2; i++) {
    s[i] = calloc((n/2), sizeof(int));
  }
  m = calloc((n/2), sizeof(int *));
  for (i = 0; i < n/2; i++) {
    m[i] = malloc((n/2)*sizeof(int));
    for (j = 0; j < n/2; j++)
      m[i][j] = -1;
  }
  res = minCostR2(frecce, s, m, 0, n-1, INT_MAX, &nCalls);
  printf ("Soluzione ricorsiva - memoization: %d chiamate\n", nCalls);
  displaySol(s, best_sol, 0, n-1);
  for (i = 0; i < n/2; i++) {
    free(s[i]);
    free(m[i]);
  }
  free(s);
  free(m);
  return res;
}

int minCostR2(int *frecce, int **s, int **m, int i, int j, int minCost, int *nCalls) {
  int k, cost;

  (*nCalls)++;
  
  if (m[i/2][j/2] != -1)
    return m[i/2][j/2];
  
  if (i == j-1) {
    s[i/2][j/2] = j;
    return contaCambi(frecce, i, j);
  }
  minCost = contaCambi(frecce, i, j);
  s[i/2][j/2] = j;
  for (k=i+1; k<j; k=k+2) {
    cost = minCostR2(frecce, s, m, i, k, minCost, nCalls) + minCostR2(frecce, s, m, k+1, j, minCost, nCalls);
    if (cost < minCost) {
      minCost = cost;
      s[i/2][j/2] = k;
    }
  }
  m[i/2][j/2] = minCost;
  return minCost;
}


int SolProgrDin(int *frecce, int n) {
  int l, i, j, k, q, **m, **s, *sol, res;
  m = calloc((n/2), sizeof(int *));
  s = calloc((n/2), sizeof(int *));
  sol = calloc(n, sizeof(int));
  for (i = 0; i < n/2; i++) {
    m[i] = calloc((n/2), sizeof(int));
    s[i] = calloc((n/2), sizeof(int));
  }
  for (l = 1; l <= n/2; l++) {
    for (i = 0; i < n/2 - l + 1; i++) {
      j = l + i - 1;
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
  displaySol(s, sol, 0, n-1);
  printf("Soluzione Prog. Din.:\n");
  res = m[0][n/2-1];
  printf("%d\n", res);
  for(i=0; i<n; i++)
    printf("%d ", sol[i]);
  printf("\n");
  for (i = 0; i < n/2; i++) {
    free(s[i]);
    free(m[i]);
  }
  free(sol);
  free(s);
  free(m);
  return res;
}

/* funzioni ausiliarie */

void displaySol(int **s, int *sol, int i, int j) {
  if (j == s[i/2][j/2]) {
    cambiaVerso(sol, i, j);
    return;
  }
  displaySol(s, sol, i, s[i/2][j/2]);
  displaySol(s, sol, s[i/2][j/2]+1, j);
  return;
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


#define N 20

int main(int argc, char *argv[]) {

  int frecce[N] = {0,1,1,1,1,1,0,0,1,0,0,0,1,0,1,1,0,0,0,0};
  int best_sol[N] = {0};
  int i;

  for (i = 0; i < N; i++) {
    printf("%d ", frecce[i]);
  }
  printf("\n");

  printf("Disposizioni ripetute\n");
  printf("%d\n", powerset1(frecce, best_sol, N));
  for (i = 0; i < N; i++) {
    printf("%d ", best_sol[i] ^ frecce[i]);
  }
  printf("\n");

  printf("Combinazioni semplici\n");
  for (i=0;i<N;i++)
    best_sol[i]=0;
  
  printf("%d\n", powerset2(frecce, best_sol, N));
  for (i = 0; i < N; i++) {
    printf("%d ", best_sol[i] ^ frecce[i]);
  }
  printf("\n");

  printf("Soluzione Ricorsiva 3\n");
  for (i=0;i<N;i++)
    best_sol[i]=0;
  
  printf("%d\n", SolRic1(frecce, best_sol, N));
  for (i = 0; i < N; i++) {
    printf("%d ", best_sol[i]);
  }
  printf("\n");

  printf("Soluzione Ricorsiva - Memoization\n");
  for (i=0;i<N;i++)
    best_sol[i]=0;
  
  printf("%d\n", SolDinMemo(frecce, best_sol, N));
  for (i = 0; i < N; i++) {
    printf("%d ", best_sol[i]);
  }
  printf("\n");
  
  SolProgrDin(frecce, N);
  printf("\n");
  
}
