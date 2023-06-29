#ifndef SCIATORE_H_INCLUDED
#define SCIATORE_H_INCLUDED
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "autorizzazioniSciatore.h"

typedef struct{
   long cardId;
   int nVolte;
   AutorizzazioniS passaggi;
}Sciatore;

Sciatore SCIATOREcrea(long cardId);
Sciatore SCIATOREsetNull();
void SCIATOREaddPassaggio(Sciatore *s, AutorizzazioneS as);
AutorizzazioneS *SCIATOREcercaPassaggioSciatore(Sciatore s, char *skilift);
void SCIATOREprint(Sciatore s, FILE *f);
void SCIATOREclear(Sciatore s);

#endif // SCIATORE_H_INCLUDED
