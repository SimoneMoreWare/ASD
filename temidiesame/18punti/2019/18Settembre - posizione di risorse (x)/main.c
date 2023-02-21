/*   main.c
 *   @author  : Gabriele Iurlaro
 *   @  site  : http://iurlaro.com
 *   @Modified: 22/12/2020, 19:47:02
*/
#include <stdio.h>
#include <stdlib.h>

int **leggiMappa(FILE *in, int *NR, int *NC){
    int i, j, **mat;
    fscanf(in, "%d %d", NR, NC);
    mat = calloc(NR , sizeof(int*));
    for(i=0; i<NR; i++){
        mat[i] = calloc(NC, sizeof(int));
    }
    while(fscanf(in, "%d %d", &i, &j) == 2)
        mat[i][j] = -1;
    return mat;
}

int **leggiSol(FILE *in, int NR, int NC, int *k, int *z){
    int **mappasol, j,i, *risorsex, *risorsey;
    mappasol = malloc(NR * sizeof(int*));
    for(i=0; i<NR; i++){
        mappasol[i] = malloc(NC * sizeof(int));
    }
    fscanf(in, "%d %d", k, z);
    risorsex = malloc(*k * sizeof(int));
    risorsey = malloc(*k * sizeof(int));
    for(i = 0; i<*k; i++)
        fscanf(in, "%d %d", &risorsex[i], &risorsey[i]);
    for(i=0; i<NR; i++)
        for(j=0; j<NC; j++)
            fscanf(in, "%d", &mappasol[i][j]);
    return mappasol;
}
int main(){
    int NR, NC, **mappa,**sol, k, z;
    FILE *in;
    in = fopen("mappa.txt", "r");
    mappa = leggiMappa(in, &NR, &NC);
    fclose(in);
    in  = fopen("proposta.txt", "r");
    sol = leggiSol(in, NR, NC, &k, &z);
    fclose(in);
}