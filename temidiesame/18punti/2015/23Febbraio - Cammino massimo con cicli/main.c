/*   main.c
 *   @author  : Gabriele Iurlaro
 *   @  site  : http://iurlaro.com
 *   @Modified: 22/12/2020, 19:42:40
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//#define DBG

#include "grafo.h"

int main(){
    FILE *in;
    Graph G;
    char id1[31], id2[31];
    int k, p;
    in = fopen("grafo.txt", "r");
    G = GRAPHreadFile(in);
#ifdef DBG
    GRAPHprintmatrix(G);
#endif
    fclose(in);
    printf("Inserisci coppia di vertici\n>");
    scanf("%s %s", id1, id2);
    printf("Inserisci k, p:\n>");
    scanf("%d %d", &k, &p);
    GRAPHbestPathVW(G, id1, id2, k, p);
}