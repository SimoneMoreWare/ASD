#ifndef ARTICOLO_H_INCLUDED
#define ARTICOLO_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#define CAR 200

typedef struct{
    char nome[CAR], relatore[CAR], argomento[CAR];
    int slot;
}Articolo;

Articolo ARTICOLOread(FILE *f);
void ARTICOLOprint(Articolo a, FILE *f);

#endif // ARTICOLO_H_INCLUDED
