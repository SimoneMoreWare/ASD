#include <stdio.h>
#include <stdlib.h>

typedef struct elem_s {
  int col;
  int val;
} elem;

typedef struct riga_s {
  int cont;
  elem *el;
} riga;

riga *creaMat(int **m , int r, int c) {
  int i, j, count = 0;
  riga *s = (riga *) malloc(r * sizeof(riga));
  if (s == NULL)
    exit(-1);
  for(i=0; i<r; i++) {
    // Conta quanti elementi sono non-nulli in ogni riga e poi alloca di conseguenza
    count = 0;
    for(j=0; j<c; j++) {
      if (m[i][j])
        count++;
    }
    s[i].el = (elem*) malloc(count * sizeof(elem));
    if (s[i].el == NULL)
      exit(-1);
    s[i].cont = count;
    count = 0;
    // Inserisci solo gli elementi non nulli
    for(j=0; j<c; j++) {
      if (m[i][j]) {
        s[i].el[count].col = j;
        s[i].el[count++].val = m[i][j];
      }
    }
  }
  return s;
}

int accediMat(riga *s, int r, int c, int x, int y) {
  int i;
  if (x >= r || y >= c || x < 0 || y < 0)
    return 0;
  for(i=0; i<s[x].cont; i++) {
    // Se l'elemento attuale ha associato un indice di colonna pari a quello cercato
    if (s[x].el[i].col == y)
      return s[x].el[i].val;
    // Se ho superato l'indice voluto
    if (s[x].el[i].col > y)
      return 0;
  }
  return 0;
}
