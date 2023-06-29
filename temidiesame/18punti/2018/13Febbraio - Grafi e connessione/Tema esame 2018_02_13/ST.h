#ifndef ST_H_INCLUDED
#define ST_H_INCLUDED
#include "vertice.h"

typedef struct symbleTable *ST;

ST STinit(int maxD);
void STinsert(ST st, Vertice v);
int STsearch(ST st, char *id);
Vertice STgetByIndex(ST st, int index);
void STfree(ST st);

#endif // ST_H_INCLUDED
