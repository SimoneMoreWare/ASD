#ifndef CICLO_H_INCLUDED
#define CICLO_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>

typedef struct{
	int nVertici;
	int *vertici;
}Ciclo;

typedef enum{VERO, FALSO}Boolean;

Ciclo CICLOread(FILE *f);
Ciclo CICLOsetNull();
Boolean CICLOisNull(Ciclo c);
void CICLOprint(Ciclo c, FILE *f);


#endif // CICLO_H_INCLUDED
