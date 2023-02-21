#include <stdio.h>
#include <stdlib.h>

void wrapper(int V[9],int N);
void powerset_combsempl(int pos,int start,int *sol,int V[9],int N,int *stop,int k);
int checksolution(int *sol,int k);

int main(){
    int V[] = {9,8,7,6,5,4,3,2,1};
    int N=9;
    wrapper(V,N);
    return 0;
}

void wrapper(int V[9],int N){
    int pos=0;
    int start=0;
    int *sol = (int *) malloc(N*sizeof(int));
    int i;
    int stop=0;
    for(i=N;i>=1 && stop==0;i--) powerset_combsempl(pos,start,sol,V,N,&stop,i);
    free(sol);
}

void powerset_combsempl(int pos,int start,int *sol,int V[9],int N,int *stop,int k){
    int i;

    if((*stop)==1) return;

    if(pos>=k){
        //check
        if(checksolution(sol,k)){
            (*stop) = 1;
            printf("Sequenza bitonica di lunghezza massima %d\n",k);
            for(i=0;i<k;i++) printf("%d ",sol[i]);
        }
        return;
    }

    for(i=start;i<N;i++){
        sol[pos]=V[i];
        powerset_combsempl(pos+1,i+1,sol,V,N,stop,k);
    }
}

int checksolution(int *sol,int k){

    int i;
    int crescente = 1;
    int decrescente = 0;

    for(i=0;i<k-1;i++){
        if(sol[i]==sol[i+1]) return 0;

        if(sol[i]>sol[i+1] && crescente == 1){
            decrescente = 1;
            crescente = 0;
        }
        if(sol[i] < sol[i+1] && decrescente == 1){
            crescente = -1;
            decrescente = -1;
        }
    }

    if(crescente == 1 && decrescente==0) return 1;
    if(crescente == 0 && decrescente==1) return 1;
    return 0;
}
