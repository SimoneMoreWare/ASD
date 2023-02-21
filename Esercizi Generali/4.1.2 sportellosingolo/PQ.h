#ifndef PQ_H
#define PQ_H

#include "Item.h"

void    PQinit();
int     PQempty();
void    PQinsert(Item val);
Item    PQextractMax();
void    PQstore(FILE* fout);
void    PQload(FILE* fin);
int     PQsize();
void 	PQfree();

#endif
