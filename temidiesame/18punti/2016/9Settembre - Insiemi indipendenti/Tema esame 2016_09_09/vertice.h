#ifndef VERTICE_H_INCLUDED
#define VERTICE_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 21

typedef struct{
   char identificatore[MAX];
}Vertice;

typedef enum{VERO, FALSO}Boolean;

Vertice VERTICEread(FILE *f);
Vertice VERTICEsetNull();
Boolean VERTICEisNull(Vertice v);
void VERTICEprint(Vertice v, FILE *f);

#endif // VERTICE_H_INCLUDED
