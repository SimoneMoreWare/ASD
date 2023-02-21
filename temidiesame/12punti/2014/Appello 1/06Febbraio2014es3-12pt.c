#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

void contoCorrente(int *vett, int *mark, int *sol, int pos, int n, int *diff_min, int *opt_sol);
int checkSol(int *diff_min, int *sol, int *vett, int n, int *opt_sol);

int main()
{
    int *vett, *opt_sol,*mark, *sol, n,i,diff_min = INT_MAX;

    printf("inserisci n: ");
    scanf("%d", &n);
    vett = malloc(n*sizeof(int));
    mark = malloc(n*sizeof(int));
    sol = malloc(n*sizeof(int));
    opt_sol = malloc(n*sizeof(int));

    printf("\n");

    for(i=0; i<n; i++){
        printf("inserisci vett[%d]: ", i);
        scanf("%d", &vett[i]);
        mark[i] = 0;
    }
    printf("\n");

    contoCorrente(vett, mark, sol, 0, n, &diff_min, opt_sol);

    printf("\nsoluzione: \n");
    for(i=0; i<n; i++){
        printf("%d ", opt_sol[i]);
    }
    return 0;
}

void contoCorrente(int *vett, int *mark, int *sol, int pos, int n, int *diff_min, int *opt_sol){
    int i,j;

    if(pos>=n){
       if(checkSol(diff_min, sol, vett,n,opt_sol)){
            for(i=0; i<n; i++){
                opt_sol[i]=sol[i];
            }
            printf("\n");
            return;
       }
    }

    for(j=0; j<n; j++){
        if(mark[j]==0){
            mark[j] = 1;
            sol[pos] = vett[j];
            contoCorrente(vett,mark,sol,pos+1,n,diff_min,opt_sol);
            mark[j]=0;
        }
    }

    return;
}

int checkSol(int *diff_min, int *sol, int *vett, int n, int *opt_sol){
    int saldo_corrente = 0, saldo_corrente_max = 0, saldo_corrente_min = INT_MAX, i;

    for(i=0; i<n; i++){
        saldo_corrente += sol[i];
        if(saldo_corrente >= saldo_corrente_max)
            saldo_corrente_max = saldo_corrente;
        if(saldo_corrente <= saldo_corrente_min)
            saldo_corrente_min = saldo_corrente;
    }

    if(saldo_corrente_max - saldo_corrente_min < *diff_min ){
        for(i=0; i<n; i++)
            printf("%d ", sol[i]);
        printf("\nsaldo corrente min: %d", saldo_corrente_min);
        printf("\nsaldo corrente max: %d", saldo_corrente_max);
        printf("\ndifferenza: %d", saldo_corrente_max - abs(saldo_corrente_min));
        *diff_min = saldo_corrente_max - abs(saldo_corrente_min);
        return 1;
    }

    return 0;
}
