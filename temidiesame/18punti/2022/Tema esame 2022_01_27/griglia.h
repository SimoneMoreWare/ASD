#ifndef GRIGLIA_H_INCLUDED
#define GRIGLIA_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#define BIANCO 0
#define NERO 1

typedef struct{
    int **griglia;
    int nr,  nc;
}Griglia;

typedef enum{VERO, FALSO}Boolean;

Griglia GRIGLIAinit(int nr, int nc);
Griglia GRIGLIAread(FILE *f);
void GRIGLIAfillRegione(Griglia *g, int rI, int cI, int base, int altezza, int value);
void GRIGLIAdeleteRegione(Griglia *g, int rI, int cI, int base, int altezza);
Boolean GRIGLIAcheckRegione(Griglia g, int rI, int cI, int base, int altezza);
int GRIGLIAareaBianco(Griglia g);
void GRIGLIAreset(Griglia *g);
int GRIGLIAgetMaxAreaBianco(Griglia g, int rI, int cI);
void GRIGLIAclear(Griglia g);

#endif // GRIGLIA_H_INCLUDED
