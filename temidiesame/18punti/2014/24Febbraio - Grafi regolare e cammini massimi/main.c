/*   main.c
 *   @author  : Gabriele Iurlaro
 *   @  site  : http://iurlaro.com
 *   @Modified: 22/12/2020, 19:41:21
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "grafo.h"

int main(int argc, char **argv){
    FILE *in;
    Graph G;
    int go = 1;
    char id[21];
    in = fopen("grafo.txt", "r");
    if(in == NULL)
        printf("Non riesco ad aprire il file.\n");
    G = GRAPHreadFile(in);
    fclose(in);
    if(isregular(G))
        printf("Il grafo e' regolare.\n");
    else
        printf("Il grafo non e' regolare.\n");
    printf("Inserisci id di un vertice:\n");
    while(go){
        printf(">");
        scanf("%s", id);
        if(strcmp(id, "fine") == 0)
            go = 0;
        GRAPHMaximumSimplePath(G, id);
    }
    return 0;
}