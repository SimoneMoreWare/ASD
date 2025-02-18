#ifndef TRIPACK_H
#define TRIPACK_H
#include <stdio.h>
#include <stdlib.h>

typedef struct Coll_t {
    int u, v, w;
} *Coll;

typedef struct TriPack_t {
    Coll *V;
    int n;
} *TriPack;

Coll COLLinit(int u, int v, int w);
void COLLfree(Coll V);
Coll COLLset(Coll V, int index, int val);
Coll COLLcopy(Coll copy);
TriPack TRIPACKinit(int maxN);
void TRIPACKfree(TriPack TP);
TriPack TRIPACKfile(FILE* file);
int TRIPACKdim(TriPack TP);
TriPack TRIPACKcopy(TriPack copy);
void TRIPACKstore(FILE* file, TriPack TP);

#endif