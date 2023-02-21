#include <stdio.h>
#include <stdlib.h>

void trovasottosequenza(int V[9],int N);
void powerset_combsempl(int pos,int start,int V[9],int *sol,int N,int k,int *stop,int *bestpath,int *lunghezzamassima);
int check(int *sol,int k);

int main(){
    int V[] = {8,9,6,4,5,7,3,2,4};
    int N = 9;
    trovasottosequenza(V,N);
    return 0;
}

void trovasottosequenza(int V[9],int N){
    int *sol = (int *) malloc(N*sizeof(int));
    int pos=0;
    int start=0;
    int i;
    int stop=0;
    int *bestpath = (int *) malloc(N*sizeof(int));
    int lunghezzamassima=0;
    for(i=N;i>=1 && stop==0;i--) powerset_combsempl(pos,start,V,sol,N,i,&stop,bestpath,&lunghezzamassima);
    printf("La sequenza ha lunghezza massima: %d\n",lunghezzamassima);
    for(i=0;i<lunghezzamassima;i++) printf("%d ",bestpath[i]);
    free(sol);
    free(bestpath);
}

void powerset_combsempl(int pos,int start,int V[9],int *sol,int N,int k,int *stop,int *bestpath,int *lunghezzamassima){

    int i;

    if((*stop)==1) return;

    if(pos>=k){
        if(check(sol,k)){
            (*stop)=1;
            (*lunghezzamassima)=k;
            for(i=0;i<k;i++) bestpath[i]=sol[i];
        }
        return;
    }

    for(i=start;i<N;i++){
            sol[pos]=V[i];
            powerset_combsempl(pos+1,i+1,V,sol,N,k,stop,bestpath,lunghezzamassima);
    }
}



int check(int *sol,int k){

    int i;

    for(i=0;i<k;i++){
        if(i%2==0 && i+1<k) if(sol[i]>=sol[i+1]) return 0;
        if(i%2!=0 && i+1<k) if(sol[i]<=sol[i+1]) return 0;
    }

    return 1;
}




