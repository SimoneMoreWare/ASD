#ifndef ST_H_INCLUDED
#define ST_H_INCLUDED
#include "vertice.h"

typedef struct symbleTable *ST;

ST STinit(int max);
void STinsert(ST st, Vertice a);
Vertice STgetVerticeByIndex(ST st, int index);
int STsearch(ST st, char *nome);
void STfree(ST st);

#endif // ST_H_INCLUDED
