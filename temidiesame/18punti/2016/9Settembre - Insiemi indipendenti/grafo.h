/*   grafo.h
 *   @author  : Gabriele Iurlaro
 *   @  site  : http://iurlaro.com
 *   @Modified: 22/12/2020, 19:42:56
*/
#ifndef GRAFO_H
#define GRAFO_H


typedef struct{int v, w;}Edge;
typedef struct grafo *Graph;

Graph GRAPHinit(int V);
void GRAPHfree(Graph t);
void GRAPHinsertE(Graph G, int id1, int id2);
void GRAPHremoveE(Graph G, int id1, int i2);
Graph GRAPHreadFile(FILE *in);
void GRAPHprintmatrix(Graph G);
int GRAPHedges(Graph G, int *v, int i);
int GRAPHgetE(Graph G);
int GRAPHgetV(Graph G);
int isIndipendent(Graph G, int *sol, int dim);
int *readSet(FILE *in, Graph G, int *dim);
void generaMaximalIndipendentSet(FILE *out, Graph G);
#endif
