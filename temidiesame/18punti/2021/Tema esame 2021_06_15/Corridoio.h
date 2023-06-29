#ifndef CORRIDOIO_H_INCLUDED
#define CORRIDOIO_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include "Scaffale.h"

typedef struct corridoio_s *Corridoio;

Corridoio CORRIDOIOinit();
Corridoio CORRIDOIOread(FILE *f);
Boolean CORRIDOIOinserisciPacco(Corridoio c, Pacco *pa, Posizione po);
void CORRIDOIOeliminaPacco(Corridoio c, Pacco *pa, Posizione po);
void CORRIDOIOprint(Corridoio c, FILE *f);
Scaffale CORRIDOIOsearchScaffale(Corridoio c, char *scaffale);
void CORRIDOIOfree(Corridoio c);



#endif // CORRIDOIO_H_INCLUDED
