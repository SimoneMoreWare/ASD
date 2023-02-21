#include <stdio.h>

#define N 8

int riga[N], mark[N], num_sol=0;

void perm_sempl(int q);
int controlla(void);
void stampa(void);

int main ( ) {
  int c;

  for (c=0; c<N; c++) {
    riga[c] = -1;
    mark[c] =0;
  }

  perm_sempl(0);

  printf("\nNumero di soluzioni trovate: %d \n", num_sol);

}

void perm_sempl(int q) {
  int c;
  if (q >= N) {
    if (controlla()) {
      num_sol++;
      stampa();
      return;
    }
    return;
  }

  for (c=0; c<N; c++)
    if (mark[c] == 0) {
      mark[c] = 1;
      riga[q] = c;
      perm_sempl(q+1);
      mark[c] = 0;
    }
  return;
}

int controlla (void) {
  int r, n, d;
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

void stampa() {
  int r, c;
  printf ("\nRisultato\n");
  for(r=0; r<N; r++) {
    for(c=0; c<N; c++)
      if (c==riga[r])
        printf ("%d", riga[r]);
      else
        printf ("*");
      printf ("\n");
  }
}

