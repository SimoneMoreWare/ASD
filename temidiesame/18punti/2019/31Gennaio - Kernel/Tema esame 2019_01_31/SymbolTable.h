#ifndef SymbolTable_h
#define SymbolTable_h

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 21

typedef struct symboltable *ST;

typedef struct {
    char nome[MAX];
}item;

item ITEMcrea(char *nome);
ST STinit(int nMax);
item STsearchbyIndex(ST st, int index);
int STsearchbyname(ST st, char *name);
int STcount(ST st);
void STinsert(ST st, item vertice);
void STfree(ST st);

#endif /* SymbolTable_h */
