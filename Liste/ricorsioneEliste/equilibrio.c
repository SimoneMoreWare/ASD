#include <stdio.h>
#include <stdlib.h>
#define N 12

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
  
int main(int argc, char *argv[]) {

  int frecce[N] = {0,1,1,1,1,1,0,0,1,0,0,0};
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

  printf("Combinazioni semplici\n");
  for (i=0;i<N;i++)
    best_sol[i]=0;
  
  printf("%d\n", powerset2(frecce, best_sol, N));
  for (i = 0; i < N; i++) {
    printf("%d ", best_sol[i] ^ frecce[i]);
  }
  
}
