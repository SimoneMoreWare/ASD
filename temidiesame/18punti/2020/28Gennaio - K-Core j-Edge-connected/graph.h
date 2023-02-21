/*   graph.h
 *   @author  : Gabriele Iurlaro
 *   @  site  : http://iurlaro.com
 *   @Modified: 22/12/2020, 19:47:30
*/
#ifndef GRAFO_H
#define GRAFO_H

#include <stdio.h>

typedef struct{int v, w;}Edge;
typedef struct grafo *Graph;

Graph GRAPHinit(int V);
void GRAPHfree(Graph t);
Graph GRAPHload(FILE *in);
void GRAPHinsertE(Graph G, int id1, int id2);
void GRAPHremoveE(Graph G, int id1, int i2);
int GRAPHgetE(Graph G);
void GRAPHprintmatrix(Graph G);
int GRAPHgetV(Graph G);
void generaKcore(Graph G, int k);
void checkisjedgeconnected(Graph G, int j);
#endif
