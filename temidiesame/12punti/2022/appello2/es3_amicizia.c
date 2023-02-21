#include <stdlib.h>
#include <stdio.h>

void wrapper(int N,int k,int M[4][4]);
void powerset_comsempl(int pos,int start,int *sol,int N,int k,int M[4][4],int *stop);
int check(int *sol,int k,int M[4][4]);

int main(){

    int M[4][4] = {
            {1,1,0,1},
            {1,1,0,1},
            {0,0,1,0},
            {1,1,0,1}
            };

    int N=4;
    int k=2;
    wrapper(N,k,M);
    return 0;
}

void wrapper(int N,int k,int M[4][4]){

    int *sol = (int *) malloc(N*sizeof(int));
    int pos=0;
    int start=0;
    int i;
    int stop=0;

    for(i=k+1;i>1 && stop==0;i--) powerset_comsempl(pos,start,sol,N,i,M,&stop);


}

void powerset_comsempl(int pos,int start,int *sol,int N,int k,int M[4][4],int *stop){

    int i;

    if((*stop)==1) return;

    if(pos>=k){
        if(check(sol,k,M)){
            (*stop)=1;
            printf("{");
            for(i=0;i<k;i++) printf("%d ",sol[i]);
            printf("}");
        }
        return;
    }

    for(i=start;i<N;i++){
        sol[pos]=i;
        powerset_comsempl(pos+1,i+1,sol,N,k,M,stop);
    }
}

int check(int *sol,int k,int M[4][4]){

    int i,j;

    for(i=0;i<k;i++){
        for(j=i+1;j<k;j++){
            if(M[sol[i]][sol[j]]==0) return 0;
        }
    }
    return 1;
}
