/*   main.c
 *   @author  : Gabriele Iurlaro
 *   @  site  : http://iurlaro.com
 *   @Modified: 22/12/2020, 19:43:15
*/
#include <stdio.h>
#include <stdlib.h>
#include "st.h"
#define INT_MAX 100000000
ST readFile(FILE *in, int *N){
    ST t;
    int n,pop,dist;
    char id[31];
    Item x;
    fscanf(in,"%d\n", &n);
    *N = n;
    t = STinit(n);
    while(fscanf(in, "%s %d %d", id, &pop, &dist) == 3){
        STinsert(t,ItemCreate(id,pop,dist));
    }
    return t;
}

int **MutuaDistanza(ST table, int N){
    int **dist,i,j;
    dist = malloc(N* sizeof(int*));
    for(i=0; i<N; i++){
        dist[i] = calloc(N, sizeof(int));
    }
    for(i=0; i<N; i++){
        for(j=0; j<N; j++){
            dist[i][j] = abs(STgetbyindex(table,i).dist-STgetbyindex(table,j).dist);
        }
    }
    return dist;
}

int SD(int *sol, int **dist, int k, int N, ST table){
    int i, d, *distMin = malloc(N* sizeof(int));
    for(i=0; i<N; i++){
        distMin[i] = INT_MAX;
    }
    for(i=0; i<k; i++){
        distMin[sol[i]] = 0;
    }
    for(i=1; i<N; i++){
        if(distMin[i-1] == INT_MAX)
            continue;
        d = distMin[i-1] + dist[i-1][i];
        distMin[i] = (d < distMin[i]) ? d : distMin[i];
    }
    for(i=N-2; i>= 0; i--){
        if(distMin[i+1] == INT_MAX)
            continue;
        d = distMin[i+1] + dist[i+1][i];
        distMin[i] = (d < distMin[i]) ? d : distMin[i];
    }
    for(i=0, d=0; i<N; i++){
        d += distMin[i]*STgetbyindex(table, i).pop;
    }
    free(distMin);
    return d;
}

void comb_semplici(int pos,int **dist, int *sol, int *bestSol, int N, int k, int start, int *bestVal, ST table){
    int i, tmpval;
    if(pos == k){
        tmpval = SD(sol, dist, k, N, table);
        if(tmpval < *bestVal){
            *bestVal = tmpval;
            for(i=0; i<k; i++)
                bestSol[i] = sol[i];
        }
        return;
    }
    for(i=start; i<N; i++){
        sol[pos] = i;
        comb_semplici(pos+1, dist, sol, bestSol, N, k, i+1, bestVal, table);
    }
}

void generaSoluzione(ST table, int **dist, int N, int k){
    int *sol, *bestsol, bestVal = INT_MAX,i;
    sol = calloc(k,sizeof(int));
    bestsol = calloc(k,sizeof(int));
    comb_semplici(0, dist, sol, bestsol, N, k, 0, &bestVal, table);
    printf("Soluzione ottima a valore %d:\n", bestVal);
    for(i=0; i<k-1; i++){
        printf("%s, ",STgetbyindex(table, bestsol[i]).name);
    }
    printf("%s ",STgetbyindex(table, bestsol[i]).name);
}

int main(int argc, char **argv){
    FILE *in1, *in2;
    int N = 0, k, i, j;
    int **dist;
    ST table = NULL;
    in1 = fopen("viaEmilia.txt", "r");
    table = readFile(in1, &N);
    fclose(in1);
    dist = MutuaDistanza(table, N);
    STprint(table);
    for(i=0; i<N; i++){
        for(j=0; j<N; j++)
            printf("%3d ",dist[i][j]);
        printf("\n");
    }
    k = atoi(argv[1]);
    generaSoluzione(table, dist, N, k);
    //Manca la parte di verifica delle due soluzioni, che, viste le funzioni
    //gia' sviluppate, è assolutamente banale.
}