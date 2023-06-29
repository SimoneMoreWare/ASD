#ifndef MAPPA_H_INCLUDED
#define MAPPA_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#define EMPTY 0
#define OSTACOLO -1

typedef struct{
   int riga, colonna;
}Ostacolo;

typedef struct {
    int **mat;
    int nr, nc, nOstacoli;
    Ostacolo *ostacoli;
}Mappa;

Ostacolo OSTACOLOcreate(int riga, int colonna);

Mappa MAPPAcreate(int nr, int nc);
Mappa MAPPAread(FILE *f);
void MAPPAclear(Mappa m);



#endif // MAPPA_H_INCLUDED
