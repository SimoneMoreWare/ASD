#include <stdio.h>

#define N 8

int riga[N];

int num_sol=0;
void disp_ripet(int q);
int controlla();
void stampa();

void main ( ) {
  int i;

  for (i=0; i<N; i++)
    riga[i] = 0;

  disp_ripet(0);

  printf("Numero di soluzioni trovate: %d \n", num_sol);
}

void disp_ripet(int q) {
  int i;
  if (q >= N) {
    if(controlla()) {
      num_sol++;
      stampa();
    }
    return;
  }
  for (i=0; i<N; i++) {
    riga[q] = i;
    disp_ripet(q+1);
  }

  return;
}

void stampa() {
  int r,c;
  printf("\nsoluzione %d\n",num_sol);
  for(r=0; r<N; r++) {
    for(c=0; c<N; c++)
      if (c==riga[r])
        printf ("%d", riga[r]);
      else
        printf ("*");
    printf ("\n");
  }
}

int controlla (void) {
  int r, n, d;
  int occ[N];

  for (r=0; r<N; r++)
    occ[r]=0;

  // controlla colonne
  for (r=0; r<N; r++)
    occ[riga[r]]++;

  for (r=0; r<N; r++)
    if (occ[r]>1)
      return 0;

  // controlla diagonali
  for (d=0; d<2*N-1; d++) {
    n=0;
    for (r=0; r<N; r++) {
      if (d==r+riga[r])
        n++;
    }
    if (n>1) return 0;
  }
  // controlla antidiagonali
  for (d=0; d<2*N-1; d++) {
    n=0;
    for (r=0; r<N; r++) {
      if (d==(r-riga[r]+N-1))
        n++;
    }
    if (n>1) return 0;
  }
  return 1;
}
