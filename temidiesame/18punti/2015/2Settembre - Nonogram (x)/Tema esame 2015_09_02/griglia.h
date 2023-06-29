#ifndef GRIGLIA_H_INCLUDED
#define GRIGLIA_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#define BIANCO 0
#define NERO 1

typedef struct{
   int **griglia, nr, nc;
}Griglia;

Griglia GRIGLIAcreate(int nr, int nc);
Griglia GRIGLIAread(int nr, int nc, FILE *f);
void GRIGLIAprint(Griglia g, FILE *f);
void GRIGLIAclear(Griglia g);

#endif // GRIGLIA_H_INCLUDED
