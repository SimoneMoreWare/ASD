#include <stdlib.h>
#include <stdio.h>

int **generamatrice(int N){
    int **mat;
    int i,j,t;
    int riga;
    mat = (int **) malloc(N*sizeof(int *));

    for(i=0;i<N;i++) mat[i] = (int *) malloc(N*sizeof(int));

    for(t=0;t<N;t++){
        riga=0;
        for(j=t;j<N;j++){
            if(riga<N && j<N){
                mat[riga][j]=t;
                mat[j][riga]=t;
            }
            riga=riga+1;
        }
    }

    return mat;
}

int main(){
    int N=5;
    int **mat;

    mat = generamatrice(N);

    for(int i=0;i<N;i++){
        for(int j=0;j<N;j++){
            printf("%d ",mat[i][j]);
        }
        printf("\n");
    }

    for(int i=0;i<N;i++) free(mat[i]);
    free(mat);

    return 0;
}
