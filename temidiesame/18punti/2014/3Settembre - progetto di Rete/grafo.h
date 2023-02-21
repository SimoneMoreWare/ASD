/*   grafo.h
 *   @author  : Gabriele Iurlaro
 *   @  site  : http://iurlaro.com
 *   @Modified: 21/12/2020, 18:28:57
*/

#ifndef GRAFO_H
#define GRAFO_H

#include <stdio.h>

typedef struct{int v, w;}Edge;
typedef struct grafo *Graph;

Graph GRAPHinit(int V);
void GRAPHfree(Graph t);
void GRAPHinsertE(Graph G, int id1, int id2);
void GRAPHremoveE(Graph G, int id1, int i2);
Graph GRAPHreadFile(FILE *in);
void GRAPHprintmatrix(Graph G);
int GRAPHedges(Graph G, Edge *v);
int GRAPHgetE(Graph G);
int GRAPHgetV(Graph G);
char *GRAPHvertexbyindex(Graph G, int index);
void GRAPHconnect(Graph G,Edge *val, int dim);
#endif
