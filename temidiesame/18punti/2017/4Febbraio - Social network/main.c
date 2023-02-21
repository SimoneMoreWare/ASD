/*   main.c
 *   @author  : Gabriele Iurlaro
 *   @  site  : http://iurlaro.com
 *   @Modified: 22/12/2020, 19:43:40
*/
#include <stdio.h>
#include <stdlib.h>

#include "grafo.h"

int main(int argc, char **argv){
    FILE *in;
    Graph G;
    char id[21];
    int *cricca,dim=0;
    in = fopen(argv[1], "r");
    G = GRAPHreadFile(in);
    fclose(in);
    in = fopen(argv[2], "r");
    cricca = malloc(GRAPHgetV(G)* sizeof(int));
    while(fscanf(in, "%s", id) != EOF)
        cricca[dim++] = GRAPHgetbyName(G, id);
    if(checkCricca(G, cricca, dim))
        printf("La soluzione proposta è una cricca massimale.\n");
    else
        printf("La soluzione proposta non è uan cricca massimale.\n");
    // genera cricche massimali.
}