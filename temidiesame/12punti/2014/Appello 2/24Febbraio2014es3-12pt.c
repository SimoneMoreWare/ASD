#include <stdio.h>
#include <stdlib.h>

void disp_rip(char *val, int pos, int *mark, char *sol, int N, int n);
int checkSol(char *val,int *mark, char *sol, int N, int n);

int main()
{
    char val[5] = {'A','E','I','O','U'},*sol;
    int mark[5] = {0,0,0,0,0},N;

    printf("Inserisci N: ");
    scanf("%d", &N);

    sol=malloc(N*sizeof(char));

    disp_rip(val,0,mark,sol,N,5);

    return 0;
}

void disp_rip(char *val, int pos, int *mark, char *sol, int N, int n){
    int i;
    if(pos>=N){
        if(checkSol(val,mark,sol,N,n)){
           for(i=0; i<N;i++){
                printf("%c ", sol[i]);
            }
            printf("\n");
        }
        return;
    }
    for(i=0; i<n;i++){
        sol[pos] = val[i];
        disp_rip(val,pos+1,mark,sol,N,n);
    }
    return;
}

int checkSol(char *val,int *mark, char *sol, int N, int n){
    int i,j,is_sol = 1;

    for(i=0;i<N;i++)
        for(j=0;j<n;j++)
            if(sol[i]==val[j] && i!=j)
                mark[j]++;


    for(i=0;i<n;i++)
       if(mark[i]==0)
            is_sol = 0;

    for(i=0; i<n; i++)
        mark[i] = 0;

    if(is_sol)
        return 1;

    return 0;
}
