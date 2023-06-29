#ifndef ST_H_INCLUDED
#define ST_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include "argomento.h"

typedef struct symbleTable *ST;

ST STinit(int maxD);
void STinsert(ST st, Argomento a);
int STcount(ST st);
int STsearch(ST st, char *nome);
void STfree(ST st);

#endif // ST_H_INCLUDED
