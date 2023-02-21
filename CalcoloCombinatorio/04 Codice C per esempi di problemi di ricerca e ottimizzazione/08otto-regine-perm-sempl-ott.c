#include <stdio.h>

#define N 8
#define ND (2*N-1)

int riga[N], mark[N], diag[ND], antidiag[ND], num_sol=0;

void perm_sempl(int q);
void stampa(void);

int main ( ) {
  int i;

  for (i=0; i<N; i++) {
    riga[i] = -1;
    mark[i] =0;
  }

  for (i=0; i<ND; i++) {
    diag[i] = 0;
    antidiag[i] = 0;
  }

  perm_sempl(0);

  printf("\nNumero di soluzioni trovate: %d \n", num_sol);

}

void perm_sempl(int q) {
  int c;
  if (q >= N) {
    num_sol++;
    stampa();
    return;
  }

  for (c=0; c<N; c++)
    if ((mark[c] == 0) && (diag[q+c]==0) && (antidiag[q-c+(N-1)]==0)  ) {
      mark[c] = 1;
      diag[q+c] = 1;
      antidiag[q-c+(N-1)] = 1;
      riga[q] = c;
      perm_sempl(q+1);
      mark[c] = 0;
      diag[q+c] = 0;
      antidiag[q-c+(N-1)] = 0;
    }
  return;
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


