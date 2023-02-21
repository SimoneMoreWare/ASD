/*   main.c
 *   @author  : Gabriele Iurlaro
 *   @  site  : http://iurlaro.com
 *   @Modified: 22/12/2020, 19:46:58
*/
#include <stdio.h>
#include <stdlib.h>

#define N 5
#define distMax 8
#define intmax 1000
int dist[N][N]={{0, 8, 10, 7, 12},
                {8, 0, 7, 9, 11},
                {10, 7, 0, 10, 9},
                {7, 9, 10, 0, 8},
                {12, 11, 9, 8, 0}};

int pop[N] = {15, 5, 50, 30, 25};
int stazComune[N] = {1, 1, 1, 1, 2};

int checkfobj1(int *sol, int stazMin){
    int i,j, flag;
    for(i=0; i<N; i++){
        flag = 0;
        for(j=0; j<stazMin; j++){
            if(dist[i][sol[j]] <= distMax)
                flag = 1;
        }
        if(flag == 0)
            return 0;
    }
    return 1;
}

int fobj2(int *sol, int numStaz){
    int i,j,min,minpos,val=0;
    for(i=0; i<N; i++){
        min = intmax;
        minpos =-1;
        for(j=0; j<numStaz; j++){
            if(dist[i][sol[j]] < min){
                min = dist[i][sol[j]];
                minpos = sol[j];
            }
        }
        val += (pop[i]*min)/sol[minpos];
    }
    return val;
}

int generaSol1R(int pos, int *sol, int stazMin, int start){
    int i;
    if(pos == stazMin){
        if(checkfobj1(sol, stazMin))
            return 1;
        return 0;
    }
    for(i=start; i<N; i++){
        sol[pos] = i;
        if(generaSol1R(pos+1, sol, stazMin, i+1))
            return 1;
    }
    return 0;
}

void generasol2R(int pos, int *sol, int *bestsol, int *bestval, int *mark, int n){
    int i, tmpval;
    if(pos == n){
        tmpval = fobj2(sol, n);
        if(tmpval < *bestval){
            *bestval = tmpval;
            for(i=0; i<N; i++)
                bestsol[i] = sol[i];
        }
        return;
    }
    for(i=0; i<n; i++){
        if(mark[i] > 0){
            sol[pos]++;
            mark[i]--;
            generasol2R(pos+1, sol, bestsol, bestval, mark, n);
            sol[pos]--;
            mark[i]++;
        }
    }
}

void generasol2(int numStaz){
    int *sol, *bestsol,i, bestval = 10000;
    sol = calloc(N,  sizeof(int));
    bestsol = calloc(N, sizeof(int));
    generasol2R(0, sol, bestsol, &bestval, stazComune, numStaz);
    for(i=0; i<N; i++){
        if(bestsol[i] != 0){
            printf("%d stazioni in %d\n", sol[i], i);
        }
    }
}

void generasol1(){
    int stazMin,i, *sol;
    sol = malloc(N* sizeof(int));
    for(stazMin = 1; stazMin <N; stazMin++){
        if(generaSol1R(0, sol, stazMin, 0)){
            printf("Trovata soluzione per funzione obiettivo 1:\n(");
            for(i=0; i<stazMin; i++)
                printf(" %d ",sol[i]);
            printf(") stazMin = %d\n",stazMin);
            return;
        }
    }
}

int main() {
    generasol1();
    generasol2(2);
    return 0;
}