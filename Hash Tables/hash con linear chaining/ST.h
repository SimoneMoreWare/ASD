#ifndef ST_H_DEFINED
#define ST_H_DEFINED

typedef struct symbtab *ST;

ST  	STinit(int maxN);
void 	STinsert(ST st, Item val);
Item	STsearch(ST st, Key k);
void	STdelete(ST st, Key k);
void	STdisplay(ST st);
void    STfree(ST st);
int     STcount(ST st);
int     STempty(ST st);

#endif
