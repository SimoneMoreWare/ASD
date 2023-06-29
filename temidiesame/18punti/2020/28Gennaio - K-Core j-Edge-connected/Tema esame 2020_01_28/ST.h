#ifndef ST_H_INCLUDED
#define ST_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include "vertice.h"

typedef struct symbleTable *ST;

ST STinit(int max);
void STinsert(ST st, Vertice v);
Vertice *STsearchByIndex(ST st, int index);
int STsearchByName(ST st, char *nome);
void STfree(ST st);


#endif // ST_H_INCLUDED
