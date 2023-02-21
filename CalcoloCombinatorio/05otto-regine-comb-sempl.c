#include <stdio.h>

#define N 4

int scacchiera[N][N];

int num_sol=0;

void comb_sempl (int r0, int c0, int q);
int controlla();
void stampa();

int main ( ) {
  int r, c;

  for (r=0; r<N; r++)
    for (c=0; c<N; c++)
     scacchiera[r][c] = 0;

  comb_sempl(0,0,0);

  printf("Numero di soluzioni trovate: %d \n", num_sol);

}

void comb_sempl(int r0, int c0, int q) {
  int r,c;
  if (q == N) {
    if(controlla()) {
      num_sol++;
      stampa();
    }
    return;
  }
  for (r=r0; r<N; r++)
    for (c=0; c<N; c++)
      if (((r>r0) || ((r==r0)&&(c>=c0))) && scacchiera[r][c] == 0) {
        scacchiera[r][c] = q+1;
        comb_sempl (r,c,q+1);
        /* backtrack */
        scacchiera[r][c] = 0;
      }
  return;
}

void stampa() {
  int r,c;
  printf("\nsoluzione %d\n",num_sol);
  for(r=0; r<N; r++) {
    for(c=0; c<N; c++)
      if (scacchiera[r][c]!=0)
        printf ("Q");
      else
        printf ("*");
    printf ("\n");
  }
}

int controlla (void) {
  int r, c, d, n;
  // controlla righe
  for (r=0; r<N; r++) {
    for (c=n=0; c<N; c++) {
      if (scacchiera[r][c]!=0) n++;
    }
	if (n>1) return 0;
  }
  // controlla colonne
  for (c=0; c<N; c++) {
    for (r=n=0; r<N; r++) {
      if (scacchiera[r][c]!=0) n++;
    }
	if (n>1) return 0;
  }
  // controlla diagonali
  for (d=0; d<2*N-1; d++) {
    n=0;
    for (r=0; r<N; r++) {
      c = d-r;
      if ((c>=0)&& (c<N))
        if (scacchiera[r][c]!=0)
            n++;
    }
    if (n>1) return 0;
  }
  // controlla antidiagonali diagonali
  for (d=0; d<2*N-1; d++) {
    n=0;
    for (r=0; r<N; r++) {
      c = r-d+N-1;
      if ((c>=0)&& (c<N))
        if (scacchiera[r][c]!=0)
            n++;
    }
    if (n>1) return 0;
  }
  return 1;
}
