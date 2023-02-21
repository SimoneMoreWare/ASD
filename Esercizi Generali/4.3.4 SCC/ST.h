#ifndef TS_H_INCLUDED
#define TS_H_INCLUDED

typedef struct symboltable *ST;

ST    STinit(int maxN);
void  STfree(ST st);
int   STsize(ST st);
int   STinsert(ST st, char *str);
int   STsearch(ST st, char *str);
char *STsearchByIndex(ST st, int i);

#endif
