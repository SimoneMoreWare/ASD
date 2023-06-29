#ifndef SCAFFALE_H_INCLUDED
#define SCAFFALE_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include "Slot.h"
#define K 4

typedef struct scaffale_s *Scaffale;

Scaffale SCAFFALEinit();
Scaffale SCAFFALEread(FILE *f);
Scaffale SCAFFALEsetNull();
Boolean SCAFFALEisEmpty(Scaffale s);
char *SCAFFALEgetCode(Scaffale s);
Boolean SCAFFALEinserisciPacco(Scaffale s, Pacco *pa, Posizione po);
void SCAFFALEeliminaPacco(Scaffale s, Pacco *pa, Posizione p);
Boolean SCAFFALEcompatta(Scaffale s1, int corridoio1, Scaffale s2, int corridoio2);
void SCAFFALEsvuota(Scaffale s);
void SCAFFALEprint(Scaffale s, FILE *f);
void SCAFFALEfree(Scaffale s);


#endif // SCAFFALE_H_INCLUDED
