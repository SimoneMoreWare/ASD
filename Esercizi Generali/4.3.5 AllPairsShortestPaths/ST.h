#ifndef ST_H_INCLUDED
#define ST_H_INCLUDED

typedef struct hashtable *ST;

ST   STinit(int maxN);
void STfree(ST ht);
void STinsert(ST ht, char *str, int index);
int  STsearch(ST ht, char *str);
#endif

