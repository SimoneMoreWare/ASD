/*   main.c
 *   @author  : Gabriele Iurlaro
 *   @  site  : http://iurlaro.com
 *   @Modified: 21/12/2020, 18:29:13
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "grafo.h"
#include "queue.h"


int main(int argc, char **argv){
    FILE *in;
    Graph G;
    Edge *e;
    int i,V, dim;
    in = fopen(argv[1], "r");
    G = GRAPHreadFile(in);
    V = GRAPHgetV(G);
    e = malloc(V*(V-1)* sizeof(Edge));
    dim = GRAPHedges(G, e);
    printf("Elenco archi:\n\n");
    for(i = 0; i<dim; i++)
        printf("%d %d\n", e[i].v, e[i].w);
    GRAPHconnect(G, e, dim);
}