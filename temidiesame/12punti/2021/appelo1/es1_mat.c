#include <stdio.h>
#include <stdlib.h>
void change(int M[3][4],int r,int c);

int main(){
    int M[3][4] = {
            {1,1,3,0},
            {2,4,6,8},
            {1,2,1,1}
    };
    int r=3;
    int c=4;
    change(M,r,c);
    for(int i=0;i<r;i++){
        for(int j=0;j<c;j++){
           printf("%d ",M[i][j]);
        }
        printf("\n");
    }
    return 0;
}

void change(int M[3][4],int r,int c) {
    int i,j;
    int k,t;
    int **Mcpy = (int **) malloc(r*sizeof(int *));
    for(i=0;i<r;i++) Mcpy[i] = (int *) malloc(c*sizeof(int)); //copia della matrice
    for(i=0;i<r;i++){
        for(j=0;j<c;j++){
            if(M[i][j]%3==0){
                for(k=0;k<r;k++) Mcpy[k][j]=3;
                for(t=0;t<c;t++) Mcpy[i][t]=3;
            }else{
                if(Mcpy[i][j]!=3) Mcpy[i][j]=M[i][j]; //se la cella ha un valore diverso da 3, allora quella cella non deve avere 3
            }
        }
    }
    for(i=0;i<r;i++) for(j=0;j<c;j++) M[i][j] = Mcpy[i][j];
    for(i=0;i<r;i++) free(Mcpy[i]);
    free(Mcpy);
}
