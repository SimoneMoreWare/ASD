#include <stdio.h>

#define N 4

int s[N][N];
int num_sol=0;

void powerset (int r, int c, int q);
int controlla();
void stampa();


int main ( ) {
  int i, j;

  for (i=0; i<N; i++)
    for (j=0; j<N; j++)
      s[i][j] = 0;

  powerset(0,0,0);

  printf("Numero di soluzioni trovate: %d \n", num_sol);
  return 0;
}

void powerset (int r, int c, int q) {
  if (c>=N) {
    c=0; r++;
  }

  if (r>=N) {
    if (q!=N)
      return;
	if (controlla()) {
      num_sol++;
      stampa();
    }
    return;
  }

  s[r][c] = q+1;
  powerset (r,c+1,q+1);
  s[r][c] = 0;
  powerset (r,c+1,q);
  return;
}

int controlla (void) {
  int r, c, d, n;

  for (r=0; r<N; r++) {
    for (c=n=0; c<N; c++)
      if (s[r][c]!=0)
        n++;
	if (n>1)
      return 0;
  }
  for (c=0; c<N; c++) {
    for (r=n=0; r<N; r++)
      if (s[r][c]!=0)
        n++;
	if (n>1)
      return 0;
  }
  for (d=0; d<2*N-1; d++) {
    n=0;
    for (r=0; r<N; r++) {
      c = d-r;
      if ((c>=0)&& (c<N))
        if (s[r][c]!=0)
          n++;
    }
    if (n>1)
      return 0;
  }
  for (d=0; d<2*N-1; d++) {
    n=0;
    for (r=0; r<N; r++) {
      c = r-d+N-1;
      if ((c>=0)&& (c<N))
        if (s[r][c]!=0)
          n++;
    }
    if (n>1)
      return 0;
  }
  return 1;

}

void stampa() {
  int r,c;
  printf("\nsoluzione %d\n",num_sol);
  for(r=0; r<N; r++) {
    for(c=0; c<N; c++)
      if (s[r][c]!=0)
        printf ("Q");
      else
        printf ("*");
    printf ("\n");
  }
}
