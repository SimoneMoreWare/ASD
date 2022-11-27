#ifndef ST_H
#define ST_H

typedef struct symboltable *ST;

ST    STinit(int maxN);
void  STfree(ST st);
int   STsize(ST st);
int STinsert(ST st, char *str1, char *str2);
char *STsearchByIndexName(ST st, int i);
char *STsearchByIndexSubnet(ST st, int i);
int stgetindex(ST st, char *name);
void STsort(ST st,int *v);

#endif
