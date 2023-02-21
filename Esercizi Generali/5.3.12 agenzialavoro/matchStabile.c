#include<stdlib.h>
#include<string.h>
#include<stdio.h>

#include "ts.h"

#define MAXL 11
#define DBG 0
#define VERSIONE 0
#define LETTURA 0

TS leggiFile(int n, char *filename) {
  int i, j;
  char c[MAXL];
  FILE *in;
  TS ts;

  in = fopen(filename, "r");
  if (in == NULL)
    return NULL;

  ts = TSinit(n);
  if (ts == NULL)
    return NULL;

  for(i=0;i<n;i++) {
      fscanf(in, "%s", c);
      TSaggiungi(ts, c);
      for(j=0;j<n;j++) fscanf(in, "%*s");
  }

  fclose(in);
  return ts;
}

int **leggiMat(int n, TS tsi, TS tsj, char *filename) {
  int i, j, id_i, id_j, **mat;
  char ci[MAXL], cj[MAXL];
  FILE *in = fopen(filename, "r");

  if (in == NULL)
    return NULL;

  mat = calloc(n, sizeof(int*));
  if (mat == NULL)
    return NULL;

  for(i=0;i<n;i++) {
    mat[i] = calloc(n, sizeof(int));
    if (mat[i] == NULL) return NULL;
  }

  /* Legge le matrici e memorizza in posizione [i,j] l'ordine di preferenza [1, 2, .., N] per la coppia a_i, b_j
     in questo modo abbiamo accesso diretto, data la coppia, all'ordine che ogni scelta occuperebbe nella lista di preferenza di un certo elemento */
  for(i=0;i<n;i++) {
    fscanf(in, "%s", ci);
    id_i = TScerca(tsi, ci);
    for(j=0;j<n;j++) {
      fscanf(in, "%s", cj);
      id_j = TScerca(tsj, cj);
      mat[id_i][id_j] = j+1;
    }
  }

  fclose(in);
  return mat;
}

int **leggiMat1(int n, TS tsi, TS tsj, char *filename) {
  int i, j, id_i, id_j, **mat;
  char ci[MAXL], cj[MAXL];
  FILE *in = fopen(filename, "r");

  if (in == NULL)
    return NULL;

  mat = calloc(n, sizeof(int*));
  if (mat == NULL)
    return NULL;

  for(i=0;i<n;i++) {
    mat[i] = calloc(n, sizeof(int));
    if (mat[i] == NULL) return NULL;
  }

  /* Legge le matrici esattamente come sono date da file, dato che l'algoritmo ha bisogno di incontrare le scelte in ordine di preferenza */
  for(i=0;i<n;i++) {
    fscanf(in, "%s", ci);
    id_i = TScerca(tsi, ci);
    for(j=0;j<n;j++) {
      fscanf(in, "%s", cj);
      id_j = TScerca(tsj, cj);
      mat[id_i][j] = id_j;
    }
  }

  fclose(in);
  return mat;
}

void stampaMat(int **mat, int n, TS tsi, TS tsj) {
  int i, j;

  for(i=0;i<n;i++) {
    printf("%s > ", TSleggi(tsi, i));
    for(j=0;j<n;j++) {
      printf("(%d, %s) ", mat[i][j], TSleggi(tsj, j));
    }
    printf("\n");
  }
  printf("\n");
}

int checkStabile0(int n, int **AB, int **BA, int *matchA, int *matchB) {
  int i, j, k, stabile = 0;

  for(i=0;i<n;i++) {
    for(j=0;j<n;j++) {
      if (j!=matchA[i]) {
	for (k=0; !stabile && AB[i][k]!=j; k++) {
	  if (AB[i][k] == matchA[i]) {
	    stabile = 1;
	  }
	}
	for (k=0; !stabile && BA[j][k]!=i; k++) {
	  if (BA[j][k] == matchB[i]) {
	    stabile = 1;
	  }
	}
	if (!stabile)
          return 0;
      }
    }
  }
  return 1;
}

int checkStabile1(int n, int **AB, int **BA, int *matchA, int *matchB) {
  int i, j;

  for(i=0;i<n;i++) {
    for(j=0;j<n;j++) {
      if (j!=matchA[i]) {
	if ((AB[i][j] < AB[i][matchA[i]]) &&
	    (BA[j][i] < BA[j][matchB[j]]))
	  return 0;
      }
    }
  }
  return 1;
}

int checkStabile2(int n, int **AB, int **BA, int *matchA, int *matchB) {
  int i, j, k;

  for(i=0;i<n;i++) {
    for (k=0; AB[i][k]!=matchA[i]; k++) {
      j = AB[i][k];
      if (BA[j][i] < BA[j][matchB[j]])
	return 0;
    }
  }
  return 1;
}

int checkStabile(int n, int **AB, int **BA, int *matchA, int *matchB) {
  switch (VERSIONE) {
      case 0:
        return checkStabile0(n, AB, BA, matchA, matchB);
      case 1:
        return checkStabile1(n, AB, BA, matchA, matchB);
      case 2:
        return checkStabile2(n, AB, BA, matchA, matchB);
    }
}

int generaMatchingR(int n, int **AB, int **BA, int *mark, int pos, int *matchA, int *matchB) {
  int i;
  if (pos >= n) {
    /* terminazione e check */
#if DBG
    for(i=0;i<n;i++) printf("%d ", match[i]);
    printf("\n");
#endif

    return checkStabile(n, AB, BA, matchA, matchB);
  }
  for(i=0;i<n;i++) {
    if (!mark[i]) {
      mark[i] = 1;
      matchA[pos] = i;
      matchB[i] = pos;
      if (generaMatchingR(n, AB, BA, mark, pos+1, matchA, matchB) == 1)
        return 1;
      mark[i] = 0;
   }
  }
  return 0;
}

int* generaMatching(int n, int **AB, int **BA) {
  /* match memorizza l'assegnazione a->b, mentre matchRev memorizza l'associazione al rovescio b->a
     mark viene usato per non assegnare più volte il medesimo elemento */
  int *matchA = calloc(n, sizeof(int));
  int *matchB = calloc(n, sizeof(int));
  int *mark = calloc(n, sizeof(int));

  generaMatchingR(n, AB, BA, mark, 0, matchA, matchB);

  free(mark);
  free(matchB);

  return matchA;
}

/*
 *
 *  A è l'insieme delle persone e B è l'insieme delle aziende
 *
 */

int main(int argc, char **argv) {
  TS tsA, tsB;
  int **AB, **BA, *match, i, N;
  if (argc != 4) {
      printf("Uso: %s N <file_A> <file_B>\n", argv[0]);
      exit(-1);
  }
  N = atoi(argv[1]);
  /* Inizializza prima le due TS, poi procede alla lettura delle matrici con una seconda passata */

  tsA = leggiFile(N, argv[2]);
  if (tsA == NULL)
    exit(-1);
  tsB = leggiFile(N, argv[3]);
  if (tsB == NULL)
  exit(-1);

  /* Inizializza matrici */
  if(LETTURA == 0)
    AB = leggiMat(N, tsA, tsB, argv[2]);
  else
    AB = leggiMat1(N, tsA, tsB, argv[2]);
  if (AB == NULL) exit(-1);

  if(LETTURA == 0)
    BA = leggiMat(N, tsB, tsA, argv[3]);
  else
    BA = leggiMat1(N, tsB, tsA, argv[3]);
  if (BA == NULL) exit(-1);

#if DBG
  stampaMat(AB, N, tsA, tsB);
  stampaMat(BA, N, tsB, tsA);
#endif /* DBG */

  match = generaMatching(N, AB, BA);
  printf("Matching:\n");
  for(i=0;i<N;i++)
    printf("(%s, %s)\n", TSleggi(tsA, i), TSleggi(tsB, match[i]));
  printf("\n");

  for (i = 0; i < N; i++) {
    free(AB[i]);
  }
  free(AB);
  for (i = 0; i < N; i++) {
    free(BA[i]);
  }
  free(BA);
  free(match);
  TSlibera(tsA);
  TSlibera(tsB);
  return 0;
}
