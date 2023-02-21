#ifndef ST_H_INCLUDED
#define ST_H_INCLUDED

#include "skilift.h"

typedef struct symboltable *ST;

ST      STinit(int maxN);
void    STfree(ST t);
int     STcount(ST t);
skilift STinsert(ST t, char *str, int time);
skilift STsearch(ST t, char *str);
skilift STsearchOrInsert(ST t, char *str, int time);
skilift STsearchByIndex(ST t, int index);

#endif
