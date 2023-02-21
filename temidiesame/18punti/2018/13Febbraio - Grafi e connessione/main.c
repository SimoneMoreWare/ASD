/*   main.c
 *   @author  : Gabriele Iurlaro
 *   @  site  : http://iurlaro.com
 *   @Modified: 22/12/2020, 19:45:29
*/
#include <stdio.h>
#include <stdlib.h>
#include "Grafo.h"

void fill(FILE *in, FILE *in2, Graph G, Edge *s1, Edge *s2, int *n1, int *n2);

void check(Graph G, Edge *s1, Edge *s2, int n1, int n2){
    int d1, d2,i;
    for(i=0; i<n1; i++)
        GRAPHinsertE(G, s1[i].v, s1[i].w, 1);
    d1 = getDiameter(G, 0);
    for(i=0; i<n1; i++)
        GRAPHremoveE(G, s1[i].v, s1[i].w, 1);
    for(i=0; i<n2; i++)
        GRAPHinsertE(G, s2[i].v, s2[i].w, 1);
    d2 = getDiameter(G, 0);
    for(i=0; i<n2; i++)
        GRAPHremoveE(G, s2[i].v, s2[i].w, 1);
    printf("d1 = %d, d2 = %d", d1, d2);
    if(d1 > d2)
        printf("Sol 2 ha diametro minore.\n");
    else
        printf("Sol 1 ha diametro inferiore.\n");
}

int main(){
    Graph G;
    FILE *in, *in2;
    Edge *s1, *s2;
    int n1=0,n2=0;
    in = fopen("garfo.txt", "r");
    G = GRAPHreadFile(in);
    fclose(in);
    s1 = malloc(GRAPHgetV(G)* sizeof(Edge));
    s2 = malloc(GRAPHgetV(G)* sizeof(Edge));
    in = fopen("sol1.txt", "r");
    in2 = fopen("sol2.txt", "r");
    fill(in, in2,G, s1, s2, &n1, &n2);
    fclose(in);
    fclose(in2);
    check(G, s1,s2,n1,n2);
}