#ifndef ST_H_INCLUDED
#define ST_H_INCLUDED
#include "stanza.h"

typedef struct symbletable *ST;

ST STinit(int max);
void STinsert(ST st, Stanza s);
int STsearch(ST st, char *nome);
Stanza STgetStanza(ST st, int index);
void STfree(ST st);


#endif // ST_H_INCLUDED
