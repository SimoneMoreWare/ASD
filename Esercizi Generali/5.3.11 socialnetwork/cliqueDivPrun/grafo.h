#ifndef _G_INCLUDED
#define _G_INCLUDED

typedef struct G* graph;

graph GRAPHinit(int nV);
void  GRAPHinsertE(graph g, int src, int dst, int w);
int   GRAPHgetNV(graph g);
int GRAPHadiacenti(graph g, int x, int y);
int GRAPHgetPeso(graph g, int x, int y);
void GRAPHfree(graph g);

#endif

