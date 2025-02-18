#ifndef GRIGLIA_H_INCLUDED
#define GRIGLIA_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#define BIANCO 0
#define NERO 1
#define OCCUPATO 2

typedef struct {
   int **griglia;
   int nr, nc;
} Griglia;

Griglia GRIGLIAinit(int nr, int nc);
Griglia GRIGLIAread(FILE *f);
int GRIGLIAareaBianchi(Griglia g);
void GRIGLIAclear(Griglia g);

#endif // GRIGLIA_H_INCLUDED
