#ifndef VERTICE_H_INCLUDED
#define VERTICE_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 21

typedef enum{ROSSO, NERO}Colore;
typedef enum{VERO, FALSO}Boolean;

typedef struct{
   char identificatore[MAX];
   Colore colore;
}Vertice;

Vertice VERTICEread(FILE*f);
Vertice VERTICEsetNull();
Boolean VERTICEisNull(Vertice v);

#endif // VERTICE_H_INCLUDED
