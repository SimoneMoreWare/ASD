#ifndef DIPENDENTE_H_INCLUDED
#define DIPENDENTE_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#define CAR 21
#define MANSIONI 4

typedef enum{OPERAIO, AMMINISTRATIVO, TECNICO, INFORMATICO}Mansione;
typedef enum{VERO, FALSO}Boolean;

typedef struct{
    int matricola, competenze[MANSIONI];
    char nome[CAR], cognome[CAR];
}Dipendente;

Dipendente DIPENDENTEread(FILE *f);

#endif // DIPENDENTE_H_INCLUDED
