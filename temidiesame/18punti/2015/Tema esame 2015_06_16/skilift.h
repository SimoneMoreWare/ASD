#ifndef SKILIFT_H_INCLUDED
#define SKILIFT_H_INCLUDED
#include "autorizzazioniSkilift.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#define MAX 11

typedef struct{
   char skiliftId[MAX];
   int timeInterval;
   AutorizzazioniSk passaggi;
}Skilift;

typedef enum{VERO, FALSO}Boolean;

Skilift SKILIFTinit();
Skilift SKILIFTread(FILE *f);
Skilift SKILIFTsetNull();
void SKILIFTaddPassaggio(Skilift *s, AutorizzazioneSk as);
AutorizzazioneSk *SKILIFTcercaPassaggioSciatore(Skilift s, long sciatore);
Boolean SKILIFTisNull(Skilift s);
void SKILIFTclear(Skilift s);

#endif // SKILIFT_H_INCLUDED
