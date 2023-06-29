#ifndef ARCHI_H_INCLUDED
#define ARCHI_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include "arco.h"

typedef struct archi *Archi;

Archi ARCHIinit();
void ARCHIinsert(Archi a, Edge e);
Edge *ARCHIgetArchi(Archi a);
int ARCHIsize(Archi a);
void ARCHIfree(Archi a);

#endif // ARCHI_H_INCLUDED
