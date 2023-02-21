#include <stdio.h>
#include <stdlib.h>

#define MAXNAVI 100

void usage(char *s) {
  printf("Utilizzo: %s <n. moli> <lunghezza moli> <n. navi> <lunghezza nave 1> [lunghezza nave 2] ...\n", s);
  exit(1);
}

/* La soluzione SetPartitions (che utilizza SP_rec) e' la soluzione presente sul libro. Tale soluzione tuttavia non trova sempre correttamente l'insieme a cardinalita' minima.
La soluzione SetPartitions_fix analizza tutti possibili partizionamenti per trovare quello migliore.
Esempio di soluzione non ottima con SetPartitions: ./moli 6 10 4 6 3 4 7
*/

int SP_rec(int n, int m, int pos, int *sol, int *navi, int *usato, int lun, int lati);

int SetPartitions(int n, int *sol, int *navi, int lun, int lati) {

  int *usato = calloc(lati, sizeof(int));
  int res = SP_rec(n, 0, 0, sol, navi, usato, lun, lati);
  free(usato);
  return res;
  
}

int SP_rec(int n, int m, int pos, int *sol, int *navi, int *usato, int lun, int lati) {
  
  int i, ok;
  if (pos >= n)
    return m;
  for (i=0; i<m; i++) {
    if (usato[i]+navi[pos] <= lun) {
      sol[pos] = i;
      usato[i] += navi[pos];
      ok = SP_rec(n, m, pos+1, sol, navi, usato, lun, lati);
      if (ok)
	return ok;
      usato[i] -= navi[pos];
    }
  }
  if (m < lati) {
    sol[pos] = m;
    usato[i] += navi[pos];
    ok = SP_rec(n, m+1, pos+1, sol, navi, usato, lun, lati);
    if (ok)
      return ok;
    usato[i] -= navi[pos];
  }
  return 0;
}

void SP_rec_fix(int n, int m, int pos, int *sol, int *navi, int *usato, int lun, int lati, int *best, int *best_sol);

int SetPartitions_fix(int n, int *sol, int *navi, int lun, int lati) {

  int *usato = calloc(lati, sizeof(int));
  int *cursol = (int *) malloc(sizeof(int)*n);
  int res = lati+1;
  SP_rec_fix(n, 0, 0, cursol, navi, usato, lun, lati, &res, sol);
  free(usato);
  return res;
  
}

void SP_rec_fix(int n, int m, int pos, int *sol, int *navi, int *usato, int lun, int lati, int *best, int *best_sol) {

  int i;
  if (pos >= n) {
    if (m < *best) {
      *best = m;
      for (i=0; i < n; i++) {
	best_sol[i] = sol[i];
      }
    }
    return;
  }
  for (i=0; i<m; i++) {
    if (usato[i]+navi[pos] <= lun) {
      sol[pos] = i;
      usato[i] += navi[pos];
      SP_rec_fix(n, m, pos+1, sol, navi, usato, lun, lati, best, best_sol);
      usato[i] -= navi[pos];
    }
  }
  if (m < lati) {
    sol[pos] = m;
    usato[i] += navi[pos];
    SP_rec_fix(n, m+1, pos+1, sol, navi, usato, lun, lati, best, best_sol);
    usato[i] -= navi[pos];
  }
  return;
}  

int main(int argc, char *argv[]) {
  
  int nmoli;
  int lunmoli;
  
  int nnavi = 7;
  int *navi;
  int i;
  int *sol;
  int m = 0;
  int ltot = 0;

  if (argc < 4)
    usage(argv[0]);
  if (sscanf(argv[1], "%d", &nmoli) != 1)
    usage(argv[0]);
  if (sscanf(argv[2], "%d", &lunmoli) != 1)
    usage(argv[0]);
  if (sscanf(argv[3], "%d", &nnavi) != 1)
    usage(argv[0]);
  if (nnavi < 0 || nnavi > MAXNAVI)
    usage(argv[0]);
  if (argc < nnavi + 4)
    usage(argv[0]);

  navi = (int *) malloc(sizeof(int)*nnavi);
  for (i = 0; i < nnavi; i++) {
    if (sscanf(argv[4+i], "%d", &navi[i]) != 1 || navi[i] <= 0) {
      printf("Nave %d - lunghezza %d errata\n", i, navi[i]);
      free(navi);
      return -1;
    }
    if (navi[i] > lunmoli) {
      printf("Nessuna soluzione - nave %d troppo lunga\n", i);
      free(navi);
      return 0;
    }
    ltot += navi[i];
  }
  if (ltot > nmoli * lunmoli) {
    printf("Nessuna soluzione - lunghezza complessiva delle navi maggiore dello spazio disponibile (%d > %d)\n", ltot, nmoli*lunmoli);
    free(navi);
    return 0;
  }

  printf ("Soluzione trovata da SetPartitions:\n");
  sol = (int *) malloc(sizeof(int)*nnavi);
  m = SetPartitions(nnavi, sol, navi, lunmoli, nmoli);
  if (m == 0) {
    printf ("Nessuna soluzione su %d moli\n", nmoli);
  }
  else {
    printf ("Soluzione con %d moli:\n", m);
    for (i = 0; i < m; i++) {
      int pos;
      printf ("\tMolo %d:\n", i);
      for (pos = 0; pos < nnavi; pos++) {
  	if (sol[pos] == i) {
  	  printf("\t\tNave %d\n", pos);
  	}
      }
    }
  }

  printf ("\nSoluzione trovata da SetPartitions_fix:\n");
  m = SetPartitions_fix(nnavi, sol, navi, lunmoli, nmoli);
  if (m == 0) {
    printf ("Nessuna soluzione su %d moli\n", nmoli);
  }
  else {
    printf ("Soluzione con %d moli:\n", m);
    for (i = 0; i < m; i++) {
      int pos;
      printf ("\tMolo %d:\n", i);
      for (pos = 0; pos < nnavi; pos++) {
	if (sol[pos] == i) {
	  printf("\t\tNave %d\n", pos);
	}
      }
    }
  }
  
  free(navi);
  return 0;
  
}
