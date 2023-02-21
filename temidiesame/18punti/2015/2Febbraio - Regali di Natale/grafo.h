/*   grafo.h
 *   @author  : Gabriele Iurlaro
 *   @  site  : http://iurlaro.com
 *   @Modified: 22/12/2020, 19:42:02
*/
#ifndef GRAFO_GRAFO_H
#define GRAFO_GRAFO_H

typedef struct{int v, w;}Edge;
typedef struct grafo *Graph;

Graph GRAPHinit(int V);
void GRAPHfree(Graph t);
void GRAPHinsertE(Graph G, int id1, int id2);
void GRAPHremoveE(Graph G, int id1, int i2);
Graph GRAPHreadFile(FILE *in);
void GRAPHladjcreate(Graph G);
void GRAPHprintmatrix(Graph G);
void GRAPHprintlist(Graph G);
int GRAPHedges(Graph G, int *v, int i);
int GRAPHgetE(Graph G);
int GRAPHgetV(Graph G);
int *leggiRegali(FILE *in, Graph G);
int checkRegali(Graph G, int *regali);
int GRAPHmaximumDegree(Graph G);
char *GRAPHVertexname(Graph G, int i);
#endif //GRAFO_GRAFO_H
