/*   main.c
 *   @author  : Gabriele Iurlaro
 *   @  site  : http://iurlaro.com
 *   @Modified: 22/12/2020, 19:42:04
*/
#include <stdio.h>
#include <stdlib.h>

#include "grafo.h"

int generaPartizioni(Graph G, int n, int m, int pos, int *sol, int k){
    int i;
    if(pos >= n){
        if(m == k){
            if(checkRegali(G, sol))
                return 1;
            return 0;
        }
        return 0;
    }
    for(i=0; i<m; i++){
        sol[pos] = i;
        if(generaPartizioni(G, n, m, pos+1, sol, k))
            return 1;
    }
    sol[pos] = m;
    if(generaPartizioni(G, n, m+1, pos+1, sol, k))
        return 1;
    return 0;
}
void generaRegali(Graph G){
    int *sol,i;
    sol = malloc(GRAPHgetV(G)* sizeof(int));
    for(i = 0; i<GRAPHgetV(G); i++)
        if(generaPartizioni(G, GRAPHgetV(G), 0, 0, sol, i)) {
            printf("Soluzione ottima con %d tipologie di regali:\n",i);
            for (i = 0; i < GRAPHgetV(G); i++) {
            printf("%s tipologia %d\n",GRAPHVertexname(G,i),sol[i]+1);
             }
    }
}

int main(int argc, char **argv){
    FILE *in;
    Graph G;
    int *regali,i;
    in = fopen("amici.txt", "r");
    G = GRAPHreadFile(in);
    fclose(in);
    GRAPHprintmatrix(G);
    in  = fopen(argv[2], "r");
    regali = leggiRegali(in, G);
    fclose(in);
    if(checkRegali(G, regali))
        printf("Soluzione in input valida.\n");
    else
        printf("Soluzione in input non valida.\n");
    generaRegali(G);
}