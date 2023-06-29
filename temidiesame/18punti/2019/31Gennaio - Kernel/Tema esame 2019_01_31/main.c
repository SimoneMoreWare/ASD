#include "GRAPH.h"
#include <stdio.h>


int main(int argc, const char * argv[]) {
    int i;
    kernel k;
    int nv;
    GRAPH G = GRAPHload("grafo.txt", &nv);
    if (IsKernel("kernel.txt", G)==VERO) {
        printf("Il Sottoinsieme scelto e' un Kernel\n");
    }
    else {
        printf("Il sottoinsieme scelto non e' un Kernel\n");
    }
    k = powerset(G);

    GRAPHpath(G, k);
    printf("\n");
    GRAPHfree(G);
    return 0;
}
