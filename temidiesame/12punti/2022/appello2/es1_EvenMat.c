#include <stdio.h>
#include <stdlib.h>
void f(int M[5][4], int r, int c, int *r1,int *c1,int ***M1);

int main(){
    int M[5][4] = {
            {1,2,3,4},
            {5,6,7,8},
            {9,0,1,2},
            {3,4,5,6},
            {7,8,9,0},
    };
    int r=5;
    int c=4;
    int **M1;
    int r1;
    int c1;
    f(M,r,c,&r1,&c1,&M1);
    for(int i=0;i<r1;i++){
        for(int j=0;j<c1;j++) printf("%d ",M1[i][j]);
        printf("\n");
    }
    for(int i=0;i<c1;i++) free(M1[i]);
    free(M1);
    return 0;
}

void f(int M[5][4], int r, int c, int *r1,int *c1,int ***M1){
    int i,j;
    int k,t;
    (*r1)=r/2 + r%2;
    (*c1)=c/2 + c%2;
    (*M1) = (int **) malloc((*r1)*sizeof(int *));
    for(i=0;i<(*r1);i++) (*M1)[i] = (int *) malloc((*c1)*sizeof(int));

    for(i=0,k=0;i<r && k<(*r1);i=i+2,k++){
        for(j=0,t=0;j<c && t<(*c1);j=j+2,t++){
            (*M1)[k][t]=M[i][j];
        }
    }
}
