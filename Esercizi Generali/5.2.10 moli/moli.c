#include<stdlib.h>
#include<string.h>
#include<stdio.h>


int SP_rec(int n, int k, int len, int *navi, int *sol, int *usato, int pos, int m) {
  int i, ok;
  if (pos >= k) {
    return m;
  }

  for(i=0;i<m;i++) {
    if (usato[i]+navi[pos] > len) continue;
    sol[pos] = i;
    usato[i] += navi[pos];
    ok = SP_rec(n, k, len, navi, sol, usato, pos+1, m);
    if (ok) return ok;
    usato[i] -= navi[pos];
  }

  if (m < n) {
      sol[pos] = m;
      usato[i] += navi[pos];
      ok = SP_rec(n, k, len, navi, sol, usato, pos+1, m+1);
      if (ok) return ok;
  }

  return 0;
}

int main(int argc, char **argv) {

  int n = 4;
  int N = 2*n; /* per tenere conto che ogni molo ha due lati */
  int len = 10;
  int k = 7;
  int i, m = 0, tot = 0;
  int *usato, *sol;
  int *navi = calloc(k, sizeof(int));
  if (navi == NULL)
    return -1;
  navi[0] = 8;
  navi[1] = 3;
  navi[2] = 5;
  navi[3] = 2;
  navi[4] = 5;
  navi[5] = 2;
  navi[6] = 9;

  for(i=0;i<k;i++) {
    if (navi[i] > len) {
        printf("Nessuna soluzione\n");
        return -1;
    }
    tot += navi[i];
  }
  if (tot > N*len) {
    printf("Nessuna soluzione\n");
    return -1;
  }

  /* porzione usata per ogni i-esimo molo (lato sx in posizione 2*i, e lato dx in posizione 2*i+1) */
  usato = calloc(N, sizeof(int));
  if (usato == NULL)
    return -1;
  /* assegnazione nave-molo per ogni i-esima nave */
  sol = calloc(k, sizeof(int));
  if (sol == NULL)
    return -1;

  /* Invoca Er con m blocchi (inizialmente 0) */
  m = SP_rec(N, k, len, navi, sol, usato, 0, m);
  if (m > 0) {
    printf("Soluzione con %d moli\n", (m/2)+(m%2));
    for(i=0;i<k;i++) printf("Nave %d al molo %d (%s)\n", i, sol[i]/2, sol[i]%2 ? "dx" : "sx");
  } else {
    printf("Nessuna soluzione\n");
  }
  free(usato);
  free(sol);
  free(navi);
  return 0;
}








