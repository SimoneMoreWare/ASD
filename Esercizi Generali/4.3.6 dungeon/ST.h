#ifndef ST_H_DEFINED
#define ST_H_DEFINED

typedef struct symboltable *ST;

ST  	STinit(int maxN);
void    STfree(ST st);
void    STinsert(ST st, char *s, int v, int m, int id);
int     STsearch(ST st, char *s);
char   *STsearchNameByIndex(ST st, int i);
int     STsearchPointsByIndex(ST st, int i);
int     STsearchValueByIndex(ST st, int i);
#endif
