#include <stdio.h>
#include <stdlib.h>

void wrapper(int *S,int n,int s);
void algEr(int *sol,int *bestSol,int *max,int m,int pos,int *S,int n,int s,int *stop);
int check(int *sol,int s,int n,int *S);


int main()
{
    int n=5;
    int S[5]={9,6,2,3,3};
    int s=3;

    wrapper(S,n,s);

    return 0;
}

void wrapper(int *S,int n,int s){
    int pos=0;
    int m=2;
    int *sol=malloc(n*sizeof(int));
    int stop=0;
    int max=0;
    int i,j;
    int *bestSol=malloc(n*sizeof(int));
    algEr(sol,bestSol,&max,m,pos,S,n,s,&stop);

     for(i=0;i<2;i++){
    printf("{ ");
        for(j=0;j<n;j++){
            if(bestSol[j]==i){
                printf("%d ",S[j]);
            }
        }
                printf("}");

    }

}

void algEr(int *sol,int *bestSol,int *max,int m,int pos,int *S,int n,int s,int *stop){
    int i;
    int cnt=0,j;

    if(pos>=n){
        if(check(sol,s,n,S)==1){
        *stop=1;
        cnt=0;
        for(i=0;i<2;i++){
            for(j=0;j<n;j++){
                if(sol[j]==i)
                    cnt++;
            }
        }
        if(cnt>*max){
            *max=cnt;
            for(i=0;i<n;i++){
                bestSol[i]=sol[i];
            }
        }
        }
        return;
    }


    for(i=0;i<m;i++){
        sol[pos]=i;
        algEr(sol,bestSol,max,m,pos+1,S,n,s,stop);
    }
        sol[pos]=m;
        algEr(sol,bestSol,max,m+1,pos+1,S,n,s,stop);


}

int check(int *sol,int s,int n,int *S){
    int i,j;
    int count1=0,count2=0;

    for(i=0;i<2;i++){
        for(j=0;j<n;j++)
        if(sol[j]==i){
            if(i==0)
                count1=count1+S[j];
            else if(i==1)
                count2=count2+S[j];
        }
    }


    if(count1!=s+count2 && count1+s!=count2)
        return 0;


    return 1;

}
