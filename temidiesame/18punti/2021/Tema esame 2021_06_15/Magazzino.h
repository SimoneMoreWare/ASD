#ifndef MAGAZZINO_H_INCLUDED
#define MAGAZZINO_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include "Corridoio.h"

typedef struct magazzino_s *Magazzino;

Magazzino MAGAZZINOinit();
Magazzino MAGAZZINOread(FILE *f);
Boolean MAGAZZINOinserisciPacco(Magazzino m, Pacco *pa, Posizione po);
void MAGAZZINOeliminaPacco(Magazzino, Pacco *pa);
void MAGAZZINOspostaPacco(Magazzino m, Pacco *pa, Posizione po);
void MAGAZZINOcompattaScaffali(Magazzino m, int corridoio1, char *scaffale1, int corridoio2, char *scaffale2);
void MAGAZZINOprint(Magazzino m, FILE *f);
void MAGAZZINOfree(Magazzino m);

#endif // MAGAZZINO_H_INCLUDED
