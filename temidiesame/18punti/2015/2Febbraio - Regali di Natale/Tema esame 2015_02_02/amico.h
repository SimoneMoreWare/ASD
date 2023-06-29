#ifndef AMICO_H_INCLUDED
#define AMICO_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 16
#define EMPTY -1

typedef struct{
   char nome[MAX];
   int regalo;
}Amico;

typedef enum{VERO, FALSO}Boolean;

Amico AMICOread(FILE *f);
Amico AMICOsetNull();
Boolean AMICOisNull(Amico a);

#endif // AMICO_H_INCLUDED
