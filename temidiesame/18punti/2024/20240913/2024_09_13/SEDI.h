#ifndef SEDI_H
#define SEDI_H
#include "ELENCO.h"
#include "DISTMATR.h"

// dimenticato * per puntatore 
typedef struct sedi_t *SEDI;

SEDI SEDIinit(int maxN);
int SEDIgetN(SEDI s);
int SEDIgetNumS(SEDI s);
int SEDIisSede(SEDI s, int i);
SEDI SEDIfile(FILE* file);

#endif