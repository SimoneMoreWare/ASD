#ifndef VERTICE_H_INCLUDED
#define VERTICE_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#define CAR 11

typedef struct{
    char id[CAR];
    float x, y;
}Vertice;

Vertice VERTICEread(FILE *f);
void VERTICEprint(Vertice v, FILE *f);

#endif // VERTICE_H_INCLUDED
