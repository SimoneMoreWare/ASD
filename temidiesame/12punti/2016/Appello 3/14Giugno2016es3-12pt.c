#include <stdio.h>
#include <stdlib.h>
#define N 5

int* initialize(int n);
void copyToFinSol(int *sol, int *solFin,int k);
void printFinSol(int *solFin,int k);
void checkSol(int S[][9],int k, int n, int *sol, int *solFin);
void cover(int S[][9],int n, int k);
void coverR(int pos, int *sol, int *solFin, int start, int S[][9], int n, int k);

int main()
{
    int S[N][9] = {{1,2,3,0,0,0,0,0,0},{2,3,7,0,0,0,0,0,0},{7,8,0,0,0,0,0,0,0},{3,4,0,0,0,0,0,0,0},{4,5,6,0,0,0,0,0,0}};

    cover(S,N,3);

    return 0;
}

void printFinSol(int *solFin,int k){
    int i;

    printf("{ ");

    for(i=0;i<k;i++){
        printf("S%d ", solFin[i]+1);
    }

    printf(" }");

    return;
}

void copyToFinSol(int *sol, int *solFin, int k){
    int i;

    for(i=0;i<k;i++)
        solFin[i] = sol[i];

    return;
}

int* initialize(int n){
    int i, *vett;

    vett = malloc(n*sizeof(int));
    for(i=0;i<n;i++){
        vett[i] = 0;
    }

    return vett;
}

void checkSol(int S[][9],int k, int n, int *sol, int *solFin){
    int i,j,*key,isValid=1;

    key = initialize(8);

    for(i=0;i<k;i++){
        j=0;
        while(S[sol[i]][j]!=0){
            key[S[sol[i]][j]-1]++;
            j++;
        }
    }

    for(i=0;i <8 && isValid;i++){
        if(key[i]==0)
            isValid = 0;
    }

    if(isValid){
        copyToFinSol(sol,solFin,k);
    }

    return;
}

void coverR(int pos, int *sol, int *solFin, int start, int S[][9], int n, int k){
    int i;

    if(pos==k){
        checkSol(S,k,n,sol,solFin);
        return;
    }

    for(i=start; i<n; i++){
        sol[pos] = i;
        coverR(pos+1,sol,solFin,i+1,S,n,k);
    }

    return;
}

void cover(int S[][9],int n, int k){
    int *sol,*solFin;

    sol = malloc(k*sizeof(int));
    solFin = malloc(k*sizeof(int));

    coverR(0,sol,solFin,0,S,n,k);
    printFinSol(solFin,k);

    return;
}
