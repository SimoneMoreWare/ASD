#ifndef ST_H_INCLUDED
#define ST_H_INCLUDED
#include "vertice.h"

typedef struct symbleTable *ST;

ST STinit(int max);
void STinsert(ST st, Vertice v);
int STsearch(ST st, char *id);
Vertice STsearchByIndex(ST st, int index);
void STfree(ST st);

#endif // ST_H_INCLUDED
