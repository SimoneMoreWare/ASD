#include <stdio.h>
#include <stdlib.h>
int birthday (int *vet, int n, int m, int k);
int combinazionisemplici(int *vet,int n,int m,int k,int start,int pos,int *sol,int *mark,int cnt);

int main(){
    int vet[]={1,2,3,1,2,3};
    int n=6;
    int m=3;
    int k=2;
    int res;
    res=birthday(vet,n,m,k);
    printf("Numero di libri %d",res);
    return 0;
}

int birthday (int *vet, int n, int m, int k){
    int start = 0;
    int pos = 0;
    int *sol = (int *) malloc(k*sizeof(int));
    int *mark = calloc(m+1,sizeof(int));
    int cnt = 0;
    int res;
    res = combinazionisemplici(vet,n,m,k,start,pos,sol,mark,cnt);
    return res;
}

int combinazionisemplici(int *vet,int n,int m,int k,int start,int pos,int *sol,int *mark,int cnt){
    int i;
    if(pos>=k){
        printf("(");
        for(i=0;i<k;i++) printf("%d ",sol[i]);
        printf(")\n");
        return cnt+1;
    }

    for(i=start;i<n;i++){
        if(mark[vet[i]]==0){
            mark[vet[i]]=1;
            sol[pos]=i;
            cnt=combinazionisemplici(vet,n,m,k,i+1,pos+1,sol,mark,cnt);
            mark[vet[i]]=0;
        }
    }
    return cnt;
}
