#include <stdlib.h>
#include <stdio.h>

void f(int v1[3],int v2[4],int d1,int d2,int ***M);

int main(){
    int v1[] = {2,4,6};
    int v2[] = {1,3,5,7};
    int **M;
    int d1=3;
    int d2=4;
    int i,j;
    f(v1,v2,d1,d2,&M);
    for(i=0;i<d1;i++){
        for(j=0;j<d2;j++){
            printf("%d ",M[i][j]);
        }
        printf("\n");
    }
    return 0;
}

void f(int v1[3],int v2[4],int d1,int d2,int ***M){
    int i,j;
    (*M)=(int **) malloc(d1*sizeof(int *));
    for(i=0;i<d1;i++) (*M)[i] = (int *) malloc(d2*sizeof(int));

    for(i=0;i<d1;i++){
        for(j=0;j<d2;j++){
            (*M)[i][j]=v1[i]*v2[j];
        }
    }
}
