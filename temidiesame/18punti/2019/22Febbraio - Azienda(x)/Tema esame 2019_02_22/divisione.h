#ifndef DIVISIONE_H_INCLUDED
#define DIVISIONE_H_INCLUDED
#include "dipendente.h"

typedef struct{
    int numMinAdd, compMinTot, compTotOtt;
}Requisito;

typedef struct {
    Dipendente dip;
    int mansione;
}Associazione;

typedef struct div *Divisione;

//Requisito
Requisito REQUISITOread(FILE *f);

//Associazione
Associazione ASSOCIAZIONEcrea(Dipendente d, int mansione);
void ASSOCIAZIONEprint(Associazione a, FILE *f);

//Divisione
Divisione DIVISIONEinit();
Divisione DIVISIONEread(FILE *f);
void DIVISIONEinsert(Divisione div, Dipendente dip, int mansione);
void DIVISIONEprintAssociazioni(Divisione d, FILE *f);
int DIVISIONEgetScostamento(Divisione d, int *compTot);
Boolean DIVISIONEcheck(Divisione d, int *compTot, int *addTot);
char *DIVISIONEgetSigla(Divisione d);
Divisione DIVISIONEsetNull();
Boolean DIVISIONEisEmpty(Divisione d);
void DIVISIONEfree(Divisione d);


#endif // DIVISIONE_H_INCLUDED
