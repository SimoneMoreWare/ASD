#include <stdio.h>
#include <stdlib.h>

int **malloc2dR(int nr, int nc);
void matrMult(int **A, int **B, int **C, int nr1, int nc1, int nc2);
void free2d(int **matr, int nr);

int main (void) {
  int i, j, nr1, nc1, nr2, nc2, **A, **B, **C;


  printf("Input num. righe e colonne prima matrice: \n");
  scanf("%d %d", &nr1, &nc1);

  printf("Input num. righe e colonne seconda matrice: \n");
  scanf("%d %d", &nr2, &nc2);

  if (nc1 != nr2) {
    printf("Matrici incompatibili!\n");
    exit(0);
  }

  A = malloc2dR(nr1, nc1);
  B = malloc2dR(nr2, nc2);
  C = malloc2dR(nr1, nc2);

  printf("Input prima matrice:\n");
  for (i=0; i<nr1; i++)
    for (j=0; j<nc1; j++) {
      printf("A[%d,%d] = ", i, j);
      scanf("%d", &A[i][j]);
    }

  printf("Input seconda matrice:\n");
  for (i=0; i<nr2; i++)
    for (j=0; j<nc2; j++) {
      printf("B[%d,%d] = ", i, j);
      scanf("%d", &B[i][j]);
    }

  matrMult(A, B, C, nr1, nc1, nc2);

  printf("Matrice risultato\n");
  for (i=0; i<nr1; i++) {
    for (j=0; j<nc2; j++)
      printf("%d  ",C[i][j]);
    printf("\n");
  }
  free2d(A, nr1);
  free2d(B, nr2);
  free2d(C, nr1);

  return 1;
}

int **malloc2dR(int nr, int nc) {
  int **matr, i;
  matr = calloc(nr, sizeof(int *));
  for (i=0; i < nr; i++)
    matr[i] = calloc(nc, sizeof(int));
  return matr;
}

void matrMult(int **A, int **B, int **C, int nr1, int nc1, int nc2) {
  int i, j, k;

  for (i=0; i<nr1; i++)
    for (j=0; j<nc2; j++) {
      C[i][j] = 0;
      for (k=0; k<nc1; k++)
        C[i][j] =  C[i][j] + A[i][k]*B[k][j];
    }
  }

void free2d(int **matr, int nr) {
  int i;
  for (i=0; i<nr; i++)
    free(matr[i]);
  free(matr);
}
