#include <stdio.h>
#include <stdlib.h>
int cmpfunc (const void * a, const void * b);
void wrapper(int I[5],int dimI,int S[2],int dimS);
void powerset_combsempl(int pos,int k,int start,int *sol,int *mark,int dimI,int I[5],int dimS,int S[2],int *stop,int *cnt_sol);
int main(){
    int I[] = {1,3,4,5,5};
    int dimI = 5;
    int S[]= {7,7};
    int dimS = 2;
    wrapper(I,dimI,S,dimS);
    return 0;
}

int cmpfunc (const void * a, const void * b) {
    return ( *(int*)a - *(int*)b );
}

void wrapper(int I[5],int dimI,int S[2],int dimS){

    qsort(I,dimI,sizeof(int),cmpfunc);
    qsort(S,dimS,sizeof(int),cmpfunc);
    int i;
    // ordinando i vettore posso essere sicuro di non perdermi nessuna somma perndomi dei pezzi del powerset
    int *sol = (int *) malloc(dimI*sizeof(int));
    int *mark = (int *) calloc(dimI,sizeof(int));
    int pos=0;
    int start=0;
    int stop=0;
    int cnt_sol=0;
    for(i=1;i<=dimI && stop==0;i++) powerset_combsempl(pos,i,start,sol,mark,dimI,I,dimS,S,&stop,&cnt_sol);
    if(stop==0) printf("Non e' possibile ottenere il risultato voluto");
    else printf("E' possibile ottenere il risultato");
    free(sol);
    free(mark);
}

void powerset_combsempl(int pos,int k,int start,int *sol,int *mark,int dimI,int I[5],int dimS,int S[2],int *stop,int *cnt_sol){

    int i;
    int sommaparziale;
    if((*stop)==1) return;
    if(pos>=k){
        sommaparziale=0;
        for(i=0;i<k;i++) sommaparziale = sommaparziale + I[sol[i]];
        if(sommaparziale == S[(*cnt_sol)]){
            (*cnt_sol)++;
            for(i=0;i<k;i++) mark[sol[i]]=1;
            for(i=0;i<k;i++) printf("%d ",I[sol[i]]);
            printf("\n");
        }
        if((*cnt_sol)==dimS) (*stop)=1;
        return;
    }

    for(i=start;i<dimI;i++){
        if(mark[i]==0 && I[i]<=S[(*cnt_sol)]){
            sol[pos]=i;
            powerset_combsempl(pos+1,k,i+1,sol,mark,dimI,I,dimS,S,stop,cnt_sol);
        }
    }
}
