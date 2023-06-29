#ifndef VINCOLI_H_INCLUDED
#define VINCOLI_H_INCLUDED
#include "vincolo.h"

typedef struct{
   Vincolo *vincoli;
   int dim;
}Vincoli;

Vincoli VINCOLIread(FILE *f);
void VINCOLIclear(Vincoli v);

#endif // VINCOLI_H_INCLUDED
