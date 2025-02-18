#include "TriPack.h"

Coll COLLinit(int u, int v, int w) {
    Coll V = (Coll) malloc(sizeof(*V));

    V->u = u;
    V->v = v;
    V->w = w;
    
    return V;
}

void COLLfree(Coll V) {
    free(V);
}

Coll COLLset(Coll V, int index, int val) {
    switch(index) {
        case 0:
            V->u = val;
            break;
        case 1:
            V->v = val;
            break;
        case 2:
            V->w = val;
            break;
    }

    return V;
}

Coll COLLcopy(Coll copy) {
    Coll V = (Coll) malloc(sizeof(*V));

    V->u = copy->u;
    V->v = copy->v;
    V->w = copy->w;

    return V;
}

TriPack TRIPACKinit(int maxN) {
    TriPack TP = (TriPack) malloc(sizeof(*TP));
    int i;

    TP->V = (Coll*) malloc(maxN * sizeof(Coll));
    for (i = 0; i < maxN; i++)
        TP->V[i] = COLLinit(-1, -1, -1);
    TP->n = 0;
    
    return TP;
}

void TRIPACKfree(TriPack TP) {
    int i;

    for (i = 0; i < TP->n; i++)
        COLLfree(TP->V[i]);
    free(TP->V);
    free(TP);
}

/* 
    formato file:

    n
    u v w
    u v w
    [...]
    u v w

    con n numero di collezioni V e con u, v, w interi
    che indicano i vertici.
*/
TriPack TRIPACKfile(FILE* file) {
    TriPack TP = (TriPack) malloc(sizeof(*TP));
    int i, u, v, w;
    
    fscanf(file, "%d", &(TP->n));
    TP->V = (Coll*) malloc(TP->n*sizeof(Coll));
    for (i = 0; i < TP->n; i++)
        if (fscanf(file, "%d %d %d", &u, &v, &w) == 3)
            TP->V[i] = COLLinit(u, v, w);

    return TP;
}

int TRIPACKdim(TriPack TP) {
    return TP->n;
}

TriPack TRIPACKcopy(TriPack copy) {
    int i;
    TriPack TP = TRIPACKinit(copy->n);
    
    for (i = 0; i < copy->n; i++)
        TP->V[i] = COLLcopy(copy->V[i]);
    TP->n = copy->n;

    return TP;
}

void TRIPACKstore(FILE* file, TriPack TP) {
    int i;

    fprintf(file, "%d\n", TP->n);
    for (i = 0; i < TP->n; i++)
        fprintf(file, "%d %d %d\n", TP->V[i]->u, TP->V[i]->v, TP->V[i]->w);
}
