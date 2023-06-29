#ifndef PACCO_H_INCLUDED
#define PACCO_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#define CAR 200

typedef enum{VERO, FALSO}Boolean;

typedef struct{
    int corridoio, slot;
    char scaffale[CAR];
}Posizione;


typedef struct{
    char codice[CAR];
    Posizione pos;
}Pacco;



//---POSIZIONE---
Posizione POSIZIONEcrea(int corridoio, char *scaffale, int slot);
Posizione POSIZIONEsetNull();
Boolean POSIZIONEisEmpty(Posizione p);
void POSIZIONEprint(Posizione p, FILE *f);



//---PACCO---
Pacco PACCOread(FILE *f);
void PACCOsetPosizione(Pacco *p, int corridoio, char *scaffale, int slot);
void PACCOsvuotaPosizione(Pacco *p);
Pacco PACCOsetNull();
Boolean PACCOisNull(Pacco p);
char *PACCOgetCode(Pacco *p);
void PACCOprintPosizione(Pacco p, FILE *f);
void PACCOprintCode(Pacco p, FILE *f);
Posizione PACCOgetPosizione(Pacco p);


#endif // PACCO_H_INCLUDED
