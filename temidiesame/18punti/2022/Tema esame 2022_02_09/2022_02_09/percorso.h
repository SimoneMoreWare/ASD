#ifndef PERCORSO_H_INCLUDED
#define PERCORSO_H_INCLUDED
#include "griglia.h"
/*
    N = Nord
    S = Sud
    E = Est
    O = Ovest
*/
typedef enum {N, S, E, O} Direzione;
typedef enum {VERO, FALSO} Boolean;

/*
    Definisce la riga e la colonna da cui
    fare una determinata mossa, definita
    dalla direzione
*/
typedef struct {
    int riga, colonna;
    Direzione dir;
} Mossa;

/* 
    Definisce il percorso, formato da un
    insieme di mosse
    
    maxD = dimensione massima
    dim = dimensione effettiva
*/
typedef struct {
    Mossa *mosse;
    int maxD, dim;
} Percorso;

// MOSSA
Mossa MOSSAcreate(int riga, int colonna);
Mossa MOSSAread(FILE *f);
void MOSSAprint(Mossa m, FILE *f);

// PERCORSO
Percorso PERCORSOinit(int maxD);
Percorso PERCORSOread(FILE *f);
Boolean PERCORSOcheck(Percorso p, Griglia g, int *cambi,int AreaBianchi);
void PERCORSOinsert(Percorso *p, Mossa m);
void PERCORSOdelete(Percorso *p);
void PERCORSOsolve(Griglia g);
void PERCORSOprint(Percorso p, FILE *f);
void PERCORSOclear(Percorso p);



#endif // PERCORSO_H_INCLUDED
