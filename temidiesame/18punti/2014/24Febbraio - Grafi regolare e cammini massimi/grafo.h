/*   grafo.h
 *   @author  : Gabriele Iurlaro
 *   @  site  : http://iurlaro.com
 *   @Modified: 22/12/2020, 19:41:19
*/
#ifndef GRAFO_H
#define GRAFO_H


typedef struct{int v, w, wt;}Edge;
typedef struct grafo *Graph;

Graph GRAPHinit(int V);
void GRAPHfree(Graph t);
void GRAPHinsertE(Graph G, int id1, int id2, int wt);
void GRAPHremoveE(Graph G, int id1, int i2, int wt);
Graph GRAPHreadFile(FILE *in);
void GRAPHprintmatrix(Graph G);
int GRAPHedges(Graph G, int *v, int i);
int GRAPHgetE(Graph G);
int GRAPHgetV(Graph G);
int isregular(Graph G);
void GRAPHMaximumSimplePath(Graph G, char *id);
#endif
