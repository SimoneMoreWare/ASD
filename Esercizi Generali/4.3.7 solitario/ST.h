#ifndef ST_H_DEFINED
#define ST_H_DEFINED

#define MAXC 21

typedef struct symboltable *ST;


ST  	STinit(int maxN);
void    STfree(ST st);
int  	STinsert(ST st, char *s, int id);
int     STsearch(ST st, char *s);

#endif
