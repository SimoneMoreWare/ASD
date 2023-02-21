/*   main.c
 *   @author  : Gabriele Iurlaro
 *   @  site  : http://iurlaro.com
 *   @Modified: 22/12/2020, 19:46:43
*/
#include <stdio.h>
#include <stdlib.h>

#include "st.h"

ST leggiFile(int n, char *filename){
    int i,j;
    char c[12];
    FILE *in;
    ST t;
    in = fopen(filename, "r");
    t = STinit(n);
    for(i=0; i<n; i++){
        fscanf(in, "%s", c);
        STinsert(t, ItemCreate(c));
        for(j=0; j<n; j++)
            fscanf(in, "%*s");
    }
    fclose(in);
    return t;
}

int **leggiMat(int n, ST tsi, ST tsj, char *filename){
    int i, j, id_i, id_j, **mat;
    char ci[12],cj[12];
    FILE *in = fopen(filename, "r");
    mat = calloc(n, sizeof(int*));
    for(i=0; i<n; i++)
        mat[i] = calloc(n, sizeof(int));
    for(i=0; i<n; i++){
        fscanf(in, "%s",ci);
        id_i = STsearchbyname(tsi, ci);
        for(j=0; j<n; j++){
            fscanf(in, "%s", cj);
            id_j = STsearchbyname(tsj, cj);
            mat[id_i][id_j] = j+1;
        }
    }
    fclose(in);
    return mat;
}

int checkStabile(int n, int **AB, int **BA, int *matchA, int *matchB) {
    int i, j, k;

    for(i=0;i<n;i++) {
        for (k=0; AB[i][k]!=matchA[i]; k++) {
            j = AB[i][k];
            if (BA[j][i] < BA[j][matchB[j]])
                return 0;
        }
    }
    return 1;
}


int generaMatchingR(int n, int **AB, int **BA, int *mark, int pos, int *matchA, int *matchB) {
    int i;
    if (pos >= n) {
        return checkStabile(n, AB, BA, matchA, matchB);
    }
    for(i=0;i<n;i++) {
        if (!mark[i]) {
            mark[i] = 1;
            matchA[pos] = i;
            matchB[i] = pos;
            if (generaMatchingR(n, AB, BA, mark, pos+1, matchA, matchB) == 1)
                return 1;
            mark[i] = 0;
        }
    }
    return 0;
}

int* generaMatching(int n, int **AB, int **BA) {
    int *matchA = calloc(n, sizeof(int));
    int *matchB = calloc(n, sizeof(int));
    int *mark = calloc(n, sizeof(int));

    generaMatchingR(n, AB, BA, mark, 0, matchA, matchB);

    free(mark);
    free(matchB);

    return matchA;
}

int main(int argc, char **argv){
    ST tsp,tsa;
    int **pa, **ap, *match, i, N;
    N = 4;
    tsp = leggiFile(N, "persone.txt");
    tsa = leggiFile(N, "aziende.txt");
    STprint(tsp);
    STprint(tsa);
    /*pa = leggiMat(N, tsp, tsa, argv[2]);
    ap = leggiMat(N, tsa, tsp, argv[3]);
    match = generaMatching(N, pa, ap);
    printf("Matching:\n");
    for(i=0; i<N; i++){
        printf("(%s,%s)\n", STgetbyindex(tsp, i).id, STgetbyindex(tsa, match[i]).id);
    }*/
    return 0;
}