/*   main.c
 *   @author  : Gabriele Iurlaro
 *   @  site  : http://iurlaro.com
 *   @Modified: 22/12/2020, 19:47:18
*/
#include <stdio.h>
#include <stdlib.h>

#include "grafo.h"

int main(int argc, char **argv){
    Graph G;
    int *sol, dim=0;
    FILE *in;
    in = fopen(argv[1], "r");
    G = GRAPHreadFile(in);
    fclose(in);
    GRAPHprintmatrix(G);
    in = fopen(argv[2], "r");
    sol = kernelRead(in, G, &dim);
    if(isKernel(G, sol, dim))
        printf("La soluzione proposta e' un kernel di G\n");
    else
        printf("La soluzione proposta non e' un kernel di G\n");
    fclose(in);
    GRAPHminimumKernel(stdout, G);
}