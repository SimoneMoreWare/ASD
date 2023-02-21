#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#define DBG 0

int check(int *f, int *sol, int n) {
  int *tmp = calloc(n, sizeof(int)), i, dx, sx;

  for (i=0; i<n; i++)
    tmp[i] = f[i] ^ sol [i];
#if DBG
      printf("frecce originali\n");
      for (i=0;i<n;i++)
        printf("%d ", f[i]);
      printf("\n");
      printf("frecce da cambiare\n");
      for (i=0; i<n; i++)
        printf("%d ", sol[i]);
      printf("\n");
      printf("nuova configurazione di frecce\n");
      for (i=0; i<n; i++)
        printf("%d ", tmp[i]);
      printf("\n\n");
#endif /* DBG */

  if (tmp[0] == 1 || tmp[n-1] == 0) {
#if DBG
    printf("configurazione illecita: tmp[0] == 1 || tmp[n-1] == 0\n");
#endif /* DBG */
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
    if ((dx-sx) !=0) {
      free(tmp);
      return 0;
    }
  }
  free(tmp);
  return 1;
}

void  powerset(int pos, int *frecce, int *sol, int n,  int curr_num,  int *best_sol, int *best_num) {
  int i, check_ok;
  if (pos == n) {
#if DBG
    printf("\n ------ Caso terminale ------ \n");
#endif /* DBG */
    check_ok = check(frecce, sol, n);
#if DBG
    printf("curr_num=%d best_num=%d verifica=%d\n", curr_num, *best_num, check_ok);
#endif /* DBG */
    if (curr_num < *best_num && check_ok) {
      *best_num = curr_num;
      for (i=0;i<n;i++)
        best_sol[i] = sol[i];
    }
    return;
  }
  sol[pos] = 0;
  powerset(pos+1, frecce, sol, n, curr_num, best_sol, best_num);
/*  if (curr_num < *best_num) { */
    sol[pos] = 1;
    powerset(pos+1, frecce, sol, n, curr_num+1, best_sol, best_num);
/*  }  */
  return;
}

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
    if (f[i] != 0 && f[i] != 1)
      exit(-1);
  }
  fclose(in);
  return f;
}

int main() {
  int N = 0;
  int *frecce = leggiFile("frecce.txt", &N);
  int *sol = calloc(N, sizeof(int));
  int *best_sol = calloc(N, sizeof(int));
  int best_num = N, i;

  powerset(0, frecce, sol, N, 0, best_sol, &best_num);

  printf("Soluzione:\n\n");
  printf("Scambio di %d elemento/i: ", best_num);
  for (i=0; i<N; i++)
    printf("%d ", best_sol[i]);
  printf("\n\n");
  printf("Configurazione finale delle frecce:\n");
  for (i=0; i<N; i++) {
    if ((frecce[i]^best_sol[i])==0)
      printf("%c", '>');
    else
      printf("%c", '<');
  }
  printf("\n");

  free(best_sol);
  free(sol);
  free(frecce);
  return 0;
}
