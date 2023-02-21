#include <stdlib.h>
#include <ctype.h>
#include <stdio.h>
/* NR e NC sovradimensionano righe e colonne */
#define NR 100
#define NC 100
#define MAXSTR 100

FILE *out = NULL;

typedef struct {
  int r, c;
} punto_t;

/* variabili globali: matrice e numero effettivo di righe/colonne */
char L[NR][NC];
int nr, nc;

punto_t sposta(punto_t p, int i0);
void stampa(int m);
int mossa (punto_t p, punto_t o, int l);


int main (int argc, char *argv[]) {
  FILE *fp;
  out = fopen("maze.out", "w");
  char riga[MAXSTR];
  int r, c;
  punto_t in, out, p;

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
  in.r = atoi(argv[2]); in.c = atoi(argv[3]);
  out.r = atoi(argv[4]); out.c = atoi(argv[5]);

  L[in.r][in.c] = '0';
  L[out.r][out.c] = '#';
  stampa(0);
  p = in;

  if (mossa(p, out, 0)) {
    printf("soluzione trovata\n");
  }
  else {
    printf("soluzione NON trovata\n");
  }

  return 0;
}

int mossa (punto_t p, punto_t o, int l) {
  int i, r;
  punto_t p1;
  l++;
  if (p.r==o.r && p.c==o.c) {
    r=1;
  }
  else for (i = r = 0; i < 4; i++) {
    p1 = sposta(p,i);
    if (p1.r!=p.r || p1.c!=p.c) {
      L[p1.r][p1.c] = (char) ('0'+l%10);
      stampa(l);
      r = mossa(p1,o,l);
      if (r>0) {
	    /* trovata una soluzione: non provare altro e ritorna */
        break;
      }
      else {
	    /* backtrack: indietro per provare un'altra soluzione */
	    L[p1.r][p1.c] = '.';
      }
    }
  }
  for (i = 0; i < l-1; i++) 
    fprintf(out, " ");
  fprintf (out, "R(%d)\n\n", l-1);
  return r;
}

punto_t sposta(punto_t p, int i) {
  int r, c;
  int spr[4] = { 0,-1, 0, 1};
  int spc[4] = {-1, 0, 1, 0};
  r = p.r+spr[i];
  c = p.c+spc[i];
  if (r >= 0 && c >= 0 && r < nr && c < nc)
    if (toupper(L[r][c])!='X' && !isdigit(L[r][c])) {
      p.r = r; p.c = c;
    }
  return p;
}


void stampa(int m) {
  int r, c;
  for (r = 0; r < nr; r++) {
    /* margine di m spazi */
    for (c = 0; c < m; c++) 
      fprintf(out, " ");
    /* riga r della matrice */
    for (c = 0; c < nc; c++) 
      fprintf(out, "%c", L[r][c]);
    /* a capo */
    fprintf(out, "\n");
  }
  fprintf(out, "\n");
}
