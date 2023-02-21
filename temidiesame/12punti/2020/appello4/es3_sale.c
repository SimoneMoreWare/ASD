#include <stdio.h>
#include <stdlib.h>

void solve(int S[4],int nS,int P[9],int nP);
void algortimodiEr(int S[4],int nS,int P[9],int nP,int k,int *sol,int m,int pos,int *stop);

int main(){
    int S[] = {4,9,11,5};
    int nS=4;
    int P[] = {2,2,3,2,6,2,4,4,3};
    int nP=9;
    solve(S,nS,P,nP);
    return 0;
}

void solve(int S[4],int nS,int P[9],int nP){
    int *sol=(int *) malloc(nP*sizeof(int));
    int pos=0;
    int blocchi;
    int stop=0;
    for(blocchi=1;blocchi<=nS && stop==0;blocchi++) algortimodiEr(S,nS,P,nP,blocchi,sol,0,pos,&stop);
}

void algortimodiEr(int S[4],int nS,int P[9],int nP,int k,int *sol,int m,int pos,int *stop){

    int i,j,t;
    int sommapersone;
    int cnt;
    int flag;
    if((*stop)==1) return;
    if(pos>=nP){
        if(m==k){
            cnt=0;
            for(i=0;i<m;i++){
               // printf("{");
                sommapersone=0;
                flag=1;
                for(j=0;j<nP;j++){
                    if(sol[j]==i){
                       // printf("%d ",P[j]);
                        sommapersone=sommapersone+P[j];
                    }
                }
                for(t=0;t<nS && flag==1;t++){
                    if(sommapersone<=S[t]){
                        cnt++;
                        flag=0;
                    }
                }
            }
            if(cnt==m){
                (*stop)=1;
                for(i=0;i<m;i++){
                    printf("{");
                    for(j=0;j<nP;j++){
                        if(sol[j]==i){
                            printf("%d ",P[j]);
                        }
                    }
                    printf("}");
                }
            }
            //printf("\n");

        }
        return;
    }

    for(i=0;i<m;i++){
        sol[pos]=i;
        algortimodiEr(S,nS,P,nP,k,sol,m,pos+1,stop);
    }
    sol[pos]=m;
    algortimodiEr(S,nS,P,nP,k,sol,m+1,pos+1,stop);

}
