#include <stdio.h>
#include <stdlib.h>

int** generaMatrice(int N);

int main()
{
    int N,**mat,i,j;

    printf("Inserisci N: ");
    scanf("%d", &N);

    mat = generaMatrice(N);

    for(i=0; i<N;i++){
        for(j=0;j<N;j++){
            printf("%d ", mat[i][j]);
        }
        printf("\n");
    }

    return 0;
}

int** generaMatrice(int N){
    int i,j,**mat;

    mat = malloc(N*sizeof(int*));
    for(i=0; i<N;i++){
       mat[i] = malloc(N*sizeof(int));
    }

    for(i=0;i<N;i++){
        for(j=0;j<N;j++){
            if(i>=j)
                mat[i][j] = i-j;
            else
                mat[i][j] = j-i;
        }
    }

    return mat;
}
