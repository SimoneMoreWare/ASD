#ifndef SERVIZI_H
#define SERVIZI_H
#include "DISTMATR.h"
#include "SEDI.h"

// dimenticato * per puntatore 
typedef struct servizi_t *SERVIZI;

// dimenticati i tipi di ritorno
SERVIZI SERVIZIinit(int N, float media);
SERVIZI SERVIZIfile(FILE* file);
int SERVIZIcount(SERVIZI s, int i);
int SERVIZIgetMaxN(SERVIZI s);
int SERVIZIgetN(SERVIZI s);
int SERVIZIgetUsedVal(SERVIZI s, int i);
SERVIZI SERVIZIupdate(SERVIZI s, int i, int val);
int checkPart(SERVIZI s, DISTMATR d, int MAXD, int MINS);

#endif