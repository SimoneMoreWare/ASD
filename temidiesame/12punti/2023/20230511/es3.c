#include <stdio.h>
#include <stdlib.h>

void pcomb(int pos,int start,int O,int S,int **M,int *sol,int k,int *blocchi,int *stop);
int check(int *sol,int **M,int O,int S,int k);
void wrapper(int **M,int O,int S);

int main()
{
    int O=5;
    int S=5;
    int **M;
    int i,j;

    M=malloc(O*sizeof(int*));
    for(i=0;i<O;i++)
        M[i]=malloc(S*sizeof(int));

    M[0][0]=1;M[0][1]=0;M[0][2]=1;M[0][3]=0;M[0][4]=0;
    M[1][0]=1;M[1][1]=1;M[1][2]=1;M[1][3]=0;M[1][4]=0;
    M[2][0]=1;M[2][1]=0;M[2][2]=0;M[2][3]=1;M[2][4]=0;
    M[3][0]=0;M[3][1]=1;M[3][2]=1;M[3][3]=0;M[3][4]=0;
    M[4][0]=0;M[4][1]=0;M[4][2]=0;M[4][3]=0;M[4][4]=1;

    for(i=0;i<O;i++){
        for(j=0;j<S;j++)
            printf("%d ",M[i][j]);
        printf("\n");
    }

    wrapper(M,O,S);

    return 0;
}

void wrapper(int **M,int O,int S){
    int *sol=malloc(S*sizeof(int));
    int start=0;
    int i,j;
    int pos=0;
    int blocchi=0;
    int stop=0;

    for(i=1;i<S && stop==0 ;i++)
        pcomb(pos,start,O,S,M,sol,i,&blocchi,&stop);

    if(!blocchi)
        printf("La sol non esite");

    free(sol);

}

void pcomb(int pos,int start,int O,int S,int **M,int *sol,int k,int *blocchi,int *stop){
    int i;

    if((*stop)==1)return;

    if(pos>=k){
        if(check(sol,M,O,S,k)){
        (*stop)=1;
        (*blocchi)=k;
        printf("{ ");
        for(i=0;i<k;i++)
            printf("%dp ",sol[i]);
        printf("\}\n");
        }
        return;
    }


    for(i=start;i<S;i++){
        sol[pos]=i;
        pcomb(pos+1,i+1,O,S,M,sol,k,blocchi,stop);
    }

}

int check(int *sol,int **M,int O,int S,int k){
    int vettS[S];
    int i,j;

    for(i=0;i<O;i++)
        vettS[i]=0;

    for(i=0;i<k;i++){
    for(j=0;j<O;j++)
       if(M[j][sol[i]]==1){
        vettS[j]=vettS[j]+1;
       }

    }

    for(i=0;i<O;i++){
        if(vettS[i]==0 || vettS[i]>1) //disgiunti
            return 0;
    }


    return 1;
}
