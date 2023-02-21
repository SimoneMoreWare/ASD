#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

void minMonete(int n, int *val, int r, int *disp);
void minMoneteR(int pos, int* sol, int* optSol, int r, int n, int *val, int *disp, int *min);
void stampaSoluzione(int n, int *optSol);
void checkSol(int *min,int n,int r,int *sol, int *optSol, int *val);

int main()
{
    int n = 3, *val,*disp, r = 30;

    val = malloc(n*sizeof(int));
    disp = malloc(n*sizeof(int));

    val[0] = 1;
    val[1] = 10;
    val[2] = 25;

    disp[0] = 10;
    disp[1] = 3;
    disp[2] = 2;

    minMonete(n,val,r,disp);

    return 0;
}
void stampaSoluzione(int n, int *optSol){
    int i;

    printf("Soluzione: ");
    for(i=0; i<n;i++)
        printf("%d ", optSol[i]);
    printf("\n");

    return;

}

void checkSol(int *min,int n,int r,int *sol, int *optSol, int *val){
    int sum = 0, tot = 0, i;

    for(i=0;i<n;i++){
        if(sol[i]>0){
            sum+=sol[i];
            tot+=val[i]*sol[i];
        }
    }

    if(sum<*min && tot==r){
        *min = sum;

        for(i=0; i<n; i++)
            optSol[i] = sol[i];
    }

    return;
}

void minMonete(int n, int *val, int r, int *disp){
    int *sol, *optSol, min = INT_MAX, i;

    sol = malloc(n*sizeof(int));
    for(i=0;i<n;i++)
        sol[i] = 0;
    optSol = malloc(n*sizeof(int));

    minMoneteR(0, sol, optSol, r, n, val, disp, &min);

    stampaSoluzione(n, optSol);

    return;
}

void minMoneteR(int pos, int* sol, int* optSol, int r, int n, int *val, int *disp, int *min){
    int i;

    if(pos>=n){
        checkSol(min,n,r,sol,optSol,val);
        return;
    }

    for(i=0; i<=disp[pos];i++){
        minMoneteR(pos+1,sol,optSol,r,n,val,disp,min);
        sol[pos]++;
    }

    sol[pos] = 0;

    return;
}
