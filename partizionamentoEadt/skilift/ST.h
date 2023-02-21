#ifndef STDEF
#define STDEF

#include "skilift.h"

typedef struct symbtab *ST;

ST STinit(int maxN);
void STfree(ST st);
void STdestroy(ST st);
int STcount(ST st);
void STdisplay(ST st, FILE *fp);
skilift STsearch(ST st, char *str);
skilift STsearchOrInsert(ST st, char *str, int time);
skilift STsearchByIndex(ST st, int index);

#endif
