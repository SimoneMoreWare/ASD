#include <stdio.h>

void displSquare(int A[2][3], int n, int m);

int main(){
    int A[2][3] = {
            {0,1,2,},
            {3,4,5}
    };

    int n=2;
    int m=3;
    displSquare(A,n,m);
    return 0;
}

void displSquare(int A[2][3], int n, int m){
    int i,j,k,t;
    int lato;

    for(lato=1;lato<=n && lato<=m;lato++){
        printf("Sottomotracici %dx%d\n",lato,lato);
        for(i=0;i<n;i++){
            for(j=0;j<m;j++){
                if((i+lato)<=n && (j+lato)<=m){
                    for(k=i;k<lato+i;k++){
                        for(t=j;t<lato+j;t++){
                            printf("%d ",A[k][t]);
                        }
                        printf("\n");
                    }
                    printf("\n");
                }
            }
        }
        printf("\n");
    }
}
