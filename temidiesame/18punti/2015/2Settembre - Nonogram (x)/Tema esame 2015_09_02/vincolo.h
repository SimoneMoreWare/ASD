#ifndef VINCOLO_H_INCLUDED
#define VINCOLO_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>

typedef struct{
   int nGruppi;
   int *dim;
   int nGruppiInseriti;
}Vincolo;

Vincolo VINCOLOread(FILE *f);
void VINCOLOclear(Vincolo v);

#endif // VINCOLO_H_INCLUDED
