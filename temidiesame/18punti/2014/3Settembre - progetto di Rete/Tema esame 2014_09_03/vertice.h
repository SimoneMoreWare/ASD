#ifndef VERTICE_H_INCLUDED
#define VERTICE_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 21

typedef struct{
   char nome[MAX];
   int grado;
}Vertice;

typedef enum{VERO, FALSO}Boolean;

Vertice VERTICEread(FILE *f);
Vertice VERTICEsetNull();
Boolean VERTICEisNull(Vertice v);
void VERTICEincrementaGrado (Vertice *v);
void VERTICEdecrementaGrado (Vertice *v);
void VERTICEazzeraGrado (Vertice *v);

#endif // VERTICE_H_INCLUDED
