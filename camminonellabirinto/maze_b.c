#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define R 50
#define C 50

typedef struct {int r; int c;} dim;
typedef struct {int lun; int semplice;} camm;

dim leggiMatrice(FILE *in, char mat[][C]);
void stampaMatrice(FILE *out, char mat[][C], dim dimensioni);
camm verificaCammino(FILE *fin, char mat[][C], dim dimensioni);

int main(int argc, char *argv[]) {
  char mat[R][C];
  dim dimensioni;
  camm cammino;
  FILE *in = fopen(argv[1], "r");
  if (in == NULL) exit(-1);
  FILE *fin = fopen(argv[2], "r"); /* Da file... */
  /* FILE *fin = stdin;               Da tastiera... */

  dimensioni = leggiMatrice(in, mat);
  stampaMatrice(stdout, mat, dimensioni);

  cammino = verificaCammino(fin, mat, dimensioni);
  if (cammino.lun ==0)
    printf("Cammino non corretto\n");
  else
    printf("Cammino %s semplice di lunghezza %d\n", 
            cammino.semplice ? "" : "non ", cammino.lun);

  fclose(in);
  fclose(fin);

  return 0;
}

dim leggiMatrice(FILE *in, char mat[][C]) {
  int i, j, nr, nc;
  dim dimensioni;

  fscanf(in, "%d %d\n", &nr, &nc);
  for (i=0; i<nr; i++) {
    for (j=0; j<nc; j++) {
      fscanf(in, "%c", &mat[i][j]);
    }
    fscanf(in, " "); /* legge a-capo ed eventuali spazi */
  }
  dimensioni.r = nr;
  dimensioni.c = nc;
  return dimensioni;
}

void stampaMatrice(FILE *out, char mat[][C], dim dimensioni) {
  int i, j;
  for (i=0; i<dimensioni.r; i++) {
    for (j=0; j<dimensioni.c; j++)
      fprintf(out, "%c", mat[i][j]);
    fprintf(out, "\n");
  }
  fprintf(out, "\n");
  return;
}

camm verificaCammino(FILE *fin, char mat[][C], dim dimensioni) {
  int X = 0, Y = 0; /* Partenza */
  int nX, nY; /* Destinazione */
  int dx, dy, i, j, lun, stepX, stepY, incammino=1;
  camm cammino;

  cammino.lun = 0;
  cammino.semplice = 1;

  printf("Inserisci passi del cammino\n");
  while((fscanf(fin, "%d %d", &dx, &dy) == 2) && incammino) {
    printf("mossa: dx=%d dy=%d\n", dx,dy);
    /* Calcolo delle nuove posizioni */
    dy = -dy; /* la riga 0 e' in alto */
    nX = X+dx;
    nY = Y+dy;

    /* Controllo se direzione corretta */
    if (dx!=0 && dy!=0 && (abs(dx) != abs(dy))) {
      cammino.lun = 0;
      cammino.semplice = 0;
      incammino = 0;
      printf("fallito: direzione scorretta dx=%d dy=%d\n", dx, -dy);
      return cammino;
    }

    stepX = stepY = 0;
    if (dx!=0) stepX = dx/abs(dx); /* +1 o -1 */
    if (dy!=0) stepY = dy/abs(dy); /* +1 o -1 */

    lun = dx!=0 ? abs(dx) : abs(dy);

    /* Controllo se dentro la matrice */
    if (nX >= dimensioni.c || nX<0 || nY >= dimensioni.r || nY<0) {
      cammino.lun = 0;
      cammino.semplice = 0;
      incammino = 0;
      printf("fallito: destinazione nX=%d nY=%d\n", nX, nY);
    } else {
      printf("mossa nella casella %d %d\n", nX, nY);
      cammino.lun += lun;
      for(i=stepX,j=stepY; lun>0; lun--, i+=stepX, j+=stepY) {
	if(mat[Y+j][X+i] == 'X') { /* Muro! */
	  cammino.lun = 0;
	  cammino.semplice = 0;
	  incammino = 0;
	}
	else if(mat[Y+j][X+i] == '+') /* Cella gia' vista! */
	  cammino.semplice = 0;
	else
	  mat[Y+j][X+i] = '+';
      }
      stampaMatrice(stdout, mat, dimensioni);
    }

    X = nX;
    Y = nY;
    if (X == (dimensioni.c-1) && Y == (dimensioni.r-1))
      incammino = 0;
  }
  return cammino;
}

