#include <stdio.h>
#include <stdlib.h>
int f(int X[16],int N);
void powerset_combsempl(int pos,int start, int k,int *sol,int *stop,int X[16],int N);
int check(int *sol,int k);

int main(){
    int X[] = {0,8,4,12,2,10,6,14,1,9,5,13,3,11,7,15};
    int N=16;
    int k;
    k=f(X,N);
    printf("sottosequenza di lunghezza massima: %d",k);
    return 0;
}

int f(int X[16],int N){

    int pos=0;
    int start=0;
    int *sol = (int *) malloc(N*sizeof(int));
    int stop = 0;
    int i;

    for(i=N;i>=1 && stop==0;i--) powerset_combsempl(pos,start,i,sol,&stop,X,N);
    free(sol);

    return i+1;
}

void powerset_combsempl(int pos,int start, int k,int *sol,int *stop,int X[16],int N){

    int i;

    if(pos>=k){
        if(check(sol,k)){
            (*stop) = 1;
            for(i=0;i<k;i++) printf("%d ",sol[i]);
            printf("\n");
        }
        return;
    }

    for(i=start;i<N;i++){
        sol[pos]=X[i];
        powerset_combsempl(pos+1,i+1,k,sol,stop,X,N);
    }
}

int check(int *sol,int k){

    int i;

    for(i=0;i<k-1;i++) if(sol[i]>=sol[i+1]) return 0;

    return 1;
}
