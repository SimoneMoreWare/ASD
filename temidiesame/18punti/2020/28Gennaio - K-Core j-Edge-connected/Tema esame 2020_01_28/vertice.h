#ifndef VERTICE_H_INCLUDED
#define VERTICE_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define CAR 11

typedef struct{
    char nome[CAR];
    int grado;
}Vertice;

Vertice VERTICEcrea(char *nome);
int VERTICEgetGrado(Vertice v);
void VERTICEprint(Vertice v, FILE *f);

#endif // VERTICE_H_INCLUDED
