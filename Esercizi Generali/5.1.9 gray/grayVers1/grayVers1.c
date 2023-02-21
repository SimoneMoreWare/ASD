#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int **malloc2dInt(int nr,int nc) {
  int i;
  int **m = malloc(nr*sizeof(int *));
  for (i=0; i<nr; i++) {
    m[i] = calloc(nc,sizeof(int));
  }
  return m;
}

void free2d(int **m, int nr) {
  int i;
  for (i=0; i<nr; i++) {
    free(m[i]);
  }
  free(m);
}

void gray(int **codici, int pos, int nbit) {
  int i, j, ncodici = 1<<(nbit-pos);

  if (pos == nbit)
    return;

  gray(codici, pos+1, nbit);

  for (i=0; i<ncodici/2; i++) {
    codici[i][pos] = 0;
    codici[ncodici/2+i][pos] = 1;
    for (j=pos+1; j<nbit; j++)
      codici[ncodici/2+i][j] = codici[ncodici/2-1-i][j];
  }

  return;
}

int main(int argc, char **argv) {
    int nbit = atoi(argv[1]);
    int i,j, n=1<<nbit; /* 2^nbit */
    int **codici = malloc2dInt(n,nbit+1);
    gray(codici,0,nbit);

    n = 1<<nbit;
    /* vettore di stringhe termina con NULL */
    for (i=0; i<n; i++) {
      for(j=0;j<nbit;j++) {
        printf("%d", codici[i][j]);
      }
      printf("\n");
    }
    free2d(codici,n);

    return 0;
}

