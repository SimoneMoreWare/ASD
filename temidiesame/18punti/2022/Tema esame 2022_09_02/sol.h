#ifndef SOL_H_INCLUDED
#define SOL_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#define MAX 16

typedef struct{
    int r, c;
    char dir;
}Posizione;

typedef struct{
   char parola[MAX];
   Posizione p;
}Scelta;

typedef struct{
    Scelta *scelte;
    int nScelte, maxD;
}Sol;

typedef enum {VERO, FALSO}Boolean;

Posizione POSIZIONEcrea(int r, int c, char dir);
Posizione POSIZIONEsetNull();
Boolean POSIZIONEisEmpty(Posizione p);
Posizione POSIZIONEread(FILE *f);
void POSIZIONEprint(Posizione p, FILE *f);

Scelta SCELTAcrea(char *parola, int rInizio, int cInizio, char direzione);
Scelta SCELTAread(FILE *f);
void SCELTAprint(Scelta s, FILE *f);

Sol SOLcrea(int maxD);
Sol SOLread(FILE *f);
void SOLprint(Sol s, FILE *f);
void SOLclear(Sol s);

#endif // SOL_H_INCLUDED
