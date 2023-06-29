#ifndef ST_H_INCLUDED
#define ST_H_INCLUDED
#include "vertice.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct symbolTable *ST;

ST STinit(int max);
void STinsert(ST st, Vertice v);
Vertice *STgetVerticeByIndex(ST st, int index);
int STgetVerticeByLabel(ST st, char *label);
void STfree(ST st);

#endif // ST_H_INCLUDED
