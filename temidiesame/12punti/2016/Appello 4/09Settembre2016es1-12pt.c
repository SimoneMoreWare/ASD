#include <stdio.h>
#include <stdlib.h>

int subMatMax(int **mat, int r, int c, int n);

int main()
{
    int **mat, r = 3, c = 4, n = 2, max, i, j;  //cambiare n,r e c da qui

    mat = malloc(r*sizeof(int*));
    for(i=0;i<r;i++)
        mat[i]=malloc(c*sizeof(int));

    for(i=0;i<r;i++){
        for(j=0;j<c;j++) {
            printf("inserisci mat[%d][%d]: ", i,j);
            scanf("%d", &mat[i][j]);
        }
    }

    printf("\n");

    max = subMatMax(mat,r,c,n);

    printf("\nmax: %d", max);

    return 0;
}

int subMatMax(int **mat, int r, int c, int n){
    int i,j,k,l,max = 0,sum;

    for(i=0; i<=r-n;i++){
        for(j=0;j<=c-n;j++){
            for(k=i, sum = 0;k<i+n; k++){
                for(l=j; l<j+n; l++){
                    sum+=mat[k][l];
                }
            }
            if(sum>max){
                max = sum;
            }
        }
    }
    return max;
}
