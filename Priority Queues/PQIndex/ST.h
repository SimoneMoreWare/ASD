#ifndef ST_H_DEFINED
#define ST_H_DEFINED

typedef struct symboltable *ST;

ST  	STinit(int maxN);
void    STfree(ST st);
void  	STinsert(ST st, Item val, int index);
int     STsearch(ST st, Item val, int *index);
void    STdisplay(ST st);
void    STchangePrio(ST st, Item val, int i);

#endif
