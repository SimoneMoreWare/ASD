#ifndef ST_H
#define ST_H

#include "Item.h"

typedef struct symboltable *ST;

ST  	STinit(int maxN);
void    STfree(ST st);
ST      STload(FILE *fin);
int     STsearch(ST st, Key k);
void    STinsert(ST st, Item val);
void    STdelete(ST st, Key k);
void    STstore(FILE *fout, ST st);

#endif
