#ifndef COPERTURA_H_INCLUDED
#define COPERTURA_H_INCLUDED
#include "mappa.h"

typedef struct{
    int riga, colonna;
}Risorsa;

typedef struct{
    int k, Z, nr, nc;
    int **mat;
    Risorsa *risorse;
}Copertura;

typedef enum{VERO, FALSO}Boolean;

//RISORSA
Risorsa RISORSAcreate(int riga, int colonna);
Risorsa RISORSAsetNull();
void RISORSAprint(Risorsa r, FILE *f);

//COPERTURA
Copertura COPERTURAcreate(int nr, int nc, int Z, int k);
Copertura COPERTURAread(Mappa m, FILE *f);
void COPERTURAprint(Copertura c, FILE *f);
void COPERTURAverifica(Copertura c, Mappa m);
void COPERTURAsolveZFisso(Mappa m, int K, int Z);
void COPERTURAclear(Copertura c);

#endif // COPERTURA_H_INCLUDED
