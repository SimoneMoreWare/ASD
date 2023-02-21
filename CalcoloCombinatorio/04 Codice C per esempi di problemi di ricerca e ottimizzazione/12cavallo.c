#include <stdlib.h>
#include <stdio.h>

int muovi(int mossa, int x, int y, int *dx, int *dy, int **scacc, int N);
void stampa(int **scacc, int N);
int **malloc2d(int N);
void free2d(int **scacc, int N);

int main(void) {
  int dx[8], dy[8], **scacc;
  int x, y, N;

  dx[0] =  2; dy[0] =  1;
  dx[1] =  1; dy[1] =  2;
  dx[2] = -1; dy[2] =  2;
  dx[3] = -2; dy[3] =  1;
  dx[4] = -2; dy[4] = -1;
  dx[5] = -1; dy[5] = -2;
  dx[6] =  1; dy[6] = -2;
  dx[7] =  2; dy[7] = -1;

  printf("Inserisci dimensione: ");
  scanf("%d", &N);
  scacc = malloc2d(N);

  printf("Inserisci posizione di partenza: ");
  scanf("%d %d", &x, &y);
  scacc[x][y] = 1;

  if (muovi(2, x, y, dx, dy, scacc, N)==1) {
    printf("Mosse del cavallo\n");
    stampa(scacc, N);
  } else
    printf("Soluzione non trovata\n");

  free2d(scacc, N);

  return 0;
}

int muovi (int mossa, int x, int y, int *dx, int *dy, int **scacc, int N) {
  int i, newx, newy;

  if (mossa == N*N+1)
    return 1;

  for (i=0; i<8; i++) {
    newx = x + dx[i];
    newy = y + dy[i];
    if ((newx<N) && (newx>=0) && (newy<N) && (newy>=0)) {
      if (scacc[newx][newy] == 0) {
        scacc[newx][newy] = mossa;
        if (muovi(mossa+1, newx, newy, dx, dy, scacc, N) == 1)
          return 1;
        scacc[newx][newy] = 0;
      }
    }
  }
  return 0;
}

void stampa(int **scacc, int N) {
  int i, j;

  for (i=0; i<N; i++) {
    for (j=0; j<N; j++)
      printf("%2d ", scacc[i][j]);
    printf("\n");
   }
}


int **malloc2d(int N) {
  int i;
  int **m = malloc(N*sizeof(int *));
  for (i=0; i<N; i++) {
    m[i] = calloc(N,sizeof(int));
  }
  return m;
}

void free2d(int **scacc, int N) {
  int i;
  for (i=0; i<N; i++) {
    free(scacc[i]);
  }
  free(scacc);
}
