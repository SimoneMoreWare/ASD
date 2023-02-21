#ifndef ST_H
#define ST_H

#include "Item.h"

typedef struct symboltable *ST;

ST  	STinit(int maxN);
void    STfree(ST st);
ST      STload(FILE *fin);
int     STsearch(ST st, Key k);

#endif
