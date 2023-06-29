#ifndef PROGRAMMA_H_INCLUDED
#define PROGRAMMA_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include "articoli.h"

typedef struct{
    int **mat, nr, nc;
}Programma;

typedef enum {VERO, FALSO}Boolean;

Programma PROGRAMMAcrea(int nr, int nc, int empty);
Boolean PROGRAMMAcheck(int nr, int nc, int empty, Articoli ar, char *nomeFile);
void PROGRAMMAinsertArticolo(Programma *p, int articolo, int room, int slot, int nSlot);
void PROGRAMMAeliminaArticolo(Programma *p, int empty, int room, int slot, int nSlot);
int PROGRAMMAargomentiDistinti(Programma p, ST argomenti, Articoli ar);
int PROGRAMMAslotVuoti(Programma p, int empty);
void PROGRAMMAprint(Programma p, Articoli a, int empty, FILE *f);
void PROGRAMMAclear(Programma p);

#endif // PROGRAMMA_H_INCLUDED
