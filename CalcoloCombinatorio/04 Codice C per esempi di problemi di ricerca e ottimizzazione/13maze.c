#include <stdlib.h>
#include <ctype.h>
#include <stdio.h>
/* NR e NC sovradimensionano righe e colonne */
#define NR 100
#define NC 100
#define MAXSTR 100

typedef struct {
  int r, c;
} punto_t;

/* variabili globali: matrice e numero effettivo di righe/colonne */
char L[NR][NC];
int nr, nc;

punto_t sposta(punto_t p, int i);
void stampa();
int mossa (punto_t partenza, punto_t arrivo);

int main (int argc, char *argv[]) {
  FILE *fp;
  char riga[MAXSTR];
  int r, c;
  punto_t ingresso, uscita;

  if (argc < 6) {
    printf("numero di argomenti insufficiente, formato corretto: \n");
    printf("%s <nome file> <ri> <ci> <ro> <co>\n", argv[0]);
  }

  fp = fopen(argv[1],"r");
  fgets(riga,MAXSTR,fp);
  sscanf (riga, "%d%d", &nr, &nc);

  for (r = 0; r < nr; r++) {
    fgets(riga,MAXSTR,fp);
    for (c = 0; c < nc; c++) {
      L[r][c] = riga[c];
    }
  }
  ingresso.r = atoi(argv[2]); ingresso.c = atoi(argv[3]);
  uscita.r = atoi(argv[4]); uscita.c = atoi(argv[5]);

  L[ingresso.r][ingresso.c] = 'I';
  L[uscita.r][uscita.c] = 'U';
  printf("configurazione iniziale\n");
  stampa();

  if (mossa(ingresso, uscita)){
    printf("soluzione trovata\n");
    stampa();
  }
  else
    printf("soluzione NON trovata\n");
  return 0;
}

int mossa (punto_t corrente, punto_t uscita) {
  int i;

  punto_t nuovo;

  if (corrente.r == uscita.r && corrente.c == uscita.c){
    L[corrente.r][corrente.c] = 'U';
    return 1;
  }


  for (i=0; i < 4; i++) {
    nuovo = sposta(corrente,i);
    if (nuovo.r!=corrente.r || nuovo.c!=corrente.c) {
      L[nuovo.r][nuovo.c] = '*';
      if (mossa(nuovo,uscita)==1)
        return 1;
      /* backtrack: indietro per provare un'altra soluzione */
      L[nuovo.r][nuovo.c] = '.';
   }
  }
  return 0;
}

punto_t sposta(punto_t punto, int i) {
  int r, c;
  int spr[4] = { 0,-1, 0, 1};
  int spc[4] = {-1, 0, 1, 0};

  r = punto.r+spr[i];
  c = punto.c+spc[i];
  if (r >= 0 && c >= 0 && r < nr && c < nc)
    if ((L[r][c])=='.' || (L[r][c])=='U'){
      punto.r = r;
      punto.c = c;
    }
  return punto;
}


void stampa() {
  int r, c;
  for (r = 0; r < nr; r++) {
    /* riga r della matrice */
    for (c = 0; c < nc; c++)
      printf("%c", L[r][c]);
    /* a capo */
    printf("\n");
  }
  printf("\n");
}
