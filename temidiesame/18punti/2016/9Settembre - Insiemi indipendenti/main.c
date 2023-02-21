/*   main.c
 *   @author  : Gabriele Iurlaro
 *   @  site  : http://iurlaro.com
 *   @Modified: 22/12/2020, 19:42:58
*/
#include <stdio.h>
#include <stdlib.h>

#include "grafo.h"

int main(int argc, char **argv){
    Graph G;
    int *sol, dimSol = 0;
    FILE *in;
    in = fopen(argv[1], "r");
    G = GRAPHreadFile(in);
    fclose(in);
    in = fopen(argv[2],"r");
    sol = readSet(in, G, &dimSol);
    fclose(in);
    if(isIndipendent(G, sol, dimSol))
        printf("L'insieme in input e' un insieme indipendente.\n");
    else
        printf("L'insieme in input non e' un insieme indipendente.\n");
    generaMaximalIndipendentSet(stdout, G);
    return 0;
}