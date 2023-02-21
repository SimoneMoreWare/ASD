#ifndef ST_H_DEFINED
#define ST_H_DEFINED

#include "Item.h"

typedef struct symboltable *ST;

ST  	STinit(int maxN);
void    STfree(ST st);
void 	STinsertByCust(ST st, Item val);
void 	STinsertByCat(ST st, Item val);
Item	STsearchByCust(ST st, Key k);
Item	STsearchByCat(ST st, Key k);
void	STdeleteByCust(ST st, Item val);
void	STdeleteByCat(ST st, Item val);
void	STlistByCust(FILE *fout, ST st);
void	STlistByCat(FILE *fout, ST st);

#endif
