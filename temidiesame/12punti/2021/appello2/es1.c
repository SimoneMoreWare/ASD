#include <stdlib.h>
#include <stdio.h>
int f(int M[4][5],int r,int c);
int main(){
    int M[4][5] = {
            {5,-2,1,0,6},
            {9,-3,1,0,-1},
            {6,7,4,-5,0},
            {1,2,3,4,5}
    };
    int r=4;
    int c=5;
    int res;
    res=f(M,r,c);
    printf("%d",res);
    return 0;

}

int f(int M[4][5],int r,int c){

    int massimo = INT_MIN;
    int i,j;
    int lato;
    int res=0;
    int k,t;
    int sommaparziale;
    int iterazioni;
    if(r<c) iterazioni=r;
    else iterazioni=c;
    for(i=0;i<r;i++) for(j=0;j<c;j++) if(M[i][j]>massimo) massimo=M[i][j];

    for(lato=1;lato<iterazioni;lato++){ //ricordati di inserire questa iterazioni sul lato della sottomatrice in modo tale che si rinizia da 0,0
        for(i=0;i<r;i++){
            for(j=0;j<c;j++){
                if(i+lato<=r && j+lato<=c){
                    sommaparziale=0;
                    for(k=i;k<i+lato;k++){
                        for(t=j;t<j+lato;t++){
                            sommaparziale=sommaparziale+M[k][t];
                        }
                    }
                    if(sommaparziale<massimo){
                        res++;
                        for(k=i;k<i+lato;k++){
                            for(t=j;t<j+lato;t++){
                                printf("%d ",M[k][t]);
                            }
                            printf("\n");
                        }
                        printf("\n");
                    }
                }
            }
        }
    }

    return res;

}
