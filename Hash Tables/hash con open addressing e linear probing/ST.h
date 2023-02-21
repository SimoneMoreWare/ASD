#ifndef ST_H_DEFINED
#define ST_H_DEFINED

typedef struct symboltable *ST;

ST  	STinit(int maxN);
void    STfree(ST st);
void 	STinsert(ST st, Item val);
Item	STsearch(ST st, Key k);
int     STcount(ST st) ;
int     STempty(ST st) ;
void	STdelete(ST, Key) ;
void	STdisplay(ST) ;

#endif
