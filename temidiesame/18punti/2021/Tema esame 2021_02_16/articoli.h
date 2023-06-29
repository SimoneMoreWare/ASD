#ifndef ARTICOLI_H_INCLUDED
#define ARTICOLI_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include "articolo.h"
#include "ST.h"

typedef struct articoli_s *Articoli;

Articoli ARTICOLIinit();
Articoli ARTICOLIread(FILE *f);
Articolo ARTICOLIgetArticolo(Articoli a, int index);
int ARTICOLIgetNumArticoli(Articoli a);
ST ARTICOLIgetArgomenti(Articoli a);
void ARTICOLIfree(Articoli a);


#endif // ARTICOLI_H_INCLUDED
