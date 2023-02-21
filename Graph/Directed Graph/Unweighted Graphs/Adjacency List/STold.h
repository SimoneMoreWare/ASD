#ifndef ST_H_DEFINED
#define ST_H_DEFINED

typedef struct symboltable *ST;

ST  	STinit(int);
void    STfree(ST);
int		STcount(ST);
void  	STinsert(ST, char *, int id);
int     STsearch(ST, char *);
char*	STsearchByIndex(ST, int);

#endif
