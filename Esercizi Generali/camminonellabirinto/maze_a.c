#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define R 50
#define C 50

typedef enum {SX, DX, GIU, SU, NO, NE, SO, SE} dir;
typedef struct {int r; int c;} dim;
typedef struct {int lun; int semplice;} camm;

dim leggiMatrice(FILE *in, char mat[][C]);
void stampaMatrice(FILE *out, char mat[][C], dim dimensioni);
camm verificaCammino(FILE *fin, char mat[][C], dim dimensioni);
dir calcolaDirezione(int dx, int dy);

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
    fscanf(in, "%*c");
  }
  fclose(in);
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

dir calcolaDirezione(int dx, int dy) {
  dir direzione;

  if (dx <0 && dy == 0)
    direzione = SX;
  if (dx > 0 && dy == 0)
    direzione = DX;
  if (dx == 0 && dy < 0)
    direzione = GIU;
  if (dx == 0 && dy > 0)
    direzione = SU;
  if (dx < 0 && dy > 0)
    direzione = NO;
  if (dx > 0 && dy > 0)
    direzione = NE;
  if (dx < 0 && dy < 0)
    direzione = SO;
  if (dx > 0 && dy < 0)
    direzione = SE;

  return direzione;
}

camm verificaCammino(FILE *fin, char mat[][C], dim dimensioni) {
  int X = 0, Y = 0; /* Partenza */
  int nX, nY; /* Destinazione */
  int dx, dy, i, step, shift, incammino=1;
  camm cammino;
  dir direzione;

  cammino.lun = 0;
  cammino.semplice = 1;

  printf("Inserisci passi del cammino\n");
  while((fscanf(fin, "%d %d", &dx, &dy) == 2) && incammino) {
    printf("mossa: dx=%d dy=%d\n", dx,dy);
    /* Calcolo delle nuove posizioni */
    nX = X+dx;
    nY = Y+(-1)*dy;
    /* Controllo se dentro la matrice */
    if (nX>=dimensioni.c || nX<0 || nY>=dimensioni.r || nY<0) {
      cammino.lun = 0;
      cammino.semplice = 0;
      incammino = 0;
      printf("fallimento: destinazione nX=%d nY=%d\n", nX, nY);
    }
    else {
      direzione = calcolaDirezione(dx, dy);
      shift = abs(dx);
      printf("mossa in direzione %d\n", direzione);
      switch (direzione) {
        case SX:
          for(i=-1, step=0;i>=dx;i--, step++) {
            if(mat[Y][X+i] == 'X') { /* Muro! */
              cammino.lun = 0;
              cammino.semplice = 0;
              incammino = 0;
            }
            else if(mat[Y][X+i] == '+') /* Cella gia' vista! */
              cammino.semplice = 0;
            else
              mat[Y][X+i] = '+';
          }
          break;
        case DX:
          for(i=1, step=0;i<=dx;i++, step++) {
            if(mat[Y][X+i] == 'X') {/* Muro! */
              cammino.lun = 0;
              cammino.semplice = 0;
              incammino = 0;
            }
            else if(mat[Y][X+i] == '+') /* Cella gia' vista! */
              cammino.semplice = 0;
            else
              mat[Y][X+i] = '+';
          }
          break;
        case GIU:
          for(i=-1, step=0;i>=dy;i--, step++) {
            if(mat[Y-i][X] == 'X') { /* Muro! */
              cammino.lun = 0;
              cammino.semplice = 0;
              incammino = 0;
            }
            else if(mat[Y-i][X] == '+') /* Cella gia' vista! */
              cammino.semplice = 0;
            else
              mat[Y-i][X] = '+';
          }
          break;
        case SU:
          for(i=+1, step=0;i<=dy;i++, step++) {
            if(mat[Y-i][X] == 'X') {/* Muro! */
              cammino.lun = 0;
              cammino.semplice = 0;
              incammino = 0;
            }
            else if(mat[Y-i][X] == '+') // Cella gia' vista!
              cammino.semplice = 0;
            else
              mat[Y-i][X] = '+';
         }
          break;
        case NO:
          for(i=1, step=0;i<=shift;i++, step++) {
            if(mat[Y-i][X-i] == 'X') {/* Muro! */
              cammino.lun = 0;
              cammino.semplice = 0;
              incammino = 0;
            }
            else if(mat[Y-i][X-i] == '+') /* Cella gia' vista! */
              cammino.semplice = 0;
            else
              mat[Y-i][X-i] = '+';
          }
          break;
        case NE:
          for(i=1, step=0;i<=shift;i++, step++) {
            if(mat[Y-i][X+i] == 'X') {// Muro!
              cammino.lun = 0;
              cammino.semplice = 0;
              incammino = 0;
            }
            else if(mat[Y-i][X+i] == '+') /* Cella gia' vista! */
              cammino.semplice = 0;
            else
              mat[Y-i][X+i] = '+';
          }
          break;
        case SO:
          for(i=1, step=0;i<=shift;i++, step++) {
            if(mat[Y+i][X-i] == 'X') {/* Muro! */
              cammino.lun = 0;
              cammino.semplice = 0;
              incammino = 0;
            }
	    else if(mat[Y+i][X-i] == '+')  /* Cella gia' vista! */
            cammino.semplice = 0;
          else
            mat[Y+i][X-i] = '+';
          }
          break;
        case SE:
          for(i=1, step=0;i<=shift;i++, step++) {
            if(mat[Y+i][X+i] == 'X') {/* Muro! */
              cammino.lun = 0;
              cammino.semplice = 0;
              incammino = 0;
            }
            else if(mat[Y+i][X+i] == '+') /* Cella gia' vista! */
              cammino.semplice = 0;
            else
              mat[Y+i][X+i] = '+';
          }
          break;
      }
      if (incammino) {
	cammino.lun += step;

	stampaMatrice(stdout, mat, dimensioni);

	X = nX;
	Y = nY;
	if (X == (dimensioni.c-1) && Y == (dimensioni.r-1))
	  incammino = 0;;
      }
    }
  }
  return cammino;
}

