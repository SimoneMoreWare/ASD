#ifndef PIATTO_H_INCLUDED
#define PIATTO_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#define CAR 101

typedef struct{
    char nome[CAR], portata[CAR], tipologia[CAR];
    float costo;
}Piatto;

Piatto PIATTOread(FILE *f);
void PIATTOprint(Piatto p, FILE *f);

#endif // PIATTO_H_INCLUDED
