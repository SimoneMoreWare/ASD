#include <stdio.h>
#include <stdlib.h>

typedef struct a {
    int si;
    int fi;
} att;

void checkSol(int pos, int n, int *sol, int *p_max, int *final_sol, att *v);
void powerset(int pos, att *v, int *sol, int n, int *p_max, int *final_sol);
void intervSel(int n, att *v);

int main()
{
    int n,i;
    att *v;


    printf("Numero attivita'? ");
    scanf("%d", &n);
    v = malloc(n*sizeof(*v));

    for(i=0; i<n; i++){
        printf("Elemento %d", i);
        printf("\n\tInserisci inizio: ");
        scanf("%d", &v[i].si);
        printf("\tInserisci fine: ");
        scanf("%d", &v[i].fi);
    }

    intervSel(n, v);
    return 0;
}

void checkSol(int pos, int n, int *sol, int *p_max, int *final_sol, att *v){
    int local_max = 0,j,i;

    for(j =0; j <n; j++){
        for(i=0; i<n; i++){
            if(i!=j && sol[j]!=0 && sol[i]!=0){
                if((v[i].si < v[j].fi)&&(v[j].si < v[i].fi))
                    return;
            }
        }
    }

    printf("\t{ ");
    for(j =0; j <n; j++){
        if(sol[j]!=0){
            local_max += v[j].fi - v[j].si;
            printf("(%d,%d) ", v[j].si, v[j].fi);
        }
    }
    printf("}\n");

    if(local_max > *p_max){
        *p_max = local_max;
        for(j =0; j <n; j++){
            final_sol[j] = sol[j];
        }
    }
}

void powerset(int pos, att *v, int *sol, int n, int *p_max, int *final_sol){
    if(pos == n){
        checkSol(pos, n, sol,p_max,final_sol,v);
        return;
    }

    sol[pos] = 0;
    powerset(pos+1,v,sol,n,p_max, final_sol);
    sol[pos] = 1;
    powerset(pos+1,v,sol,n,p_max, final_sol);
    return;
}

void intervSel(int n, att *v){
    int *final_sol, *sol, max = 0,j;

    sol = malloc(n*sizeof(int));
    final_sol = malloc(n * sizeof(int));

    powerset(0,v,sol,n,&max,final_sol);

    printf("Final Solution: \n\t{ ");

    for(j =0; j <n; j++){
        if(final_sol[j]!=0){
            printf("(%d, %d) ", v[j].si, v[j].fi);
        }
    }
    printf("}\n");
}
