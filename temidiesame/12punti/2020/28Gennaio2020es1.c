#include <stdio.h>
#include <stdlib.h>

void buildAndPrint(int *V, int N, int **M, int r, int c);
void initializeV(int N, int *V);

int main()
{
    int *V, N = 14,**M, r=3, c=5,i;

    M = malloc(r*sizeof(int*));
    V = malloc(N*sizeof(int));

    for(i=0;i<r;i++)
        M[i] = malloc(c*sizeof(int));

    initializeV(N, V);
    buildAndPrint(V,N,M,r,c);

    return 0;
}



void buildAndPrint(int *V, int N, int **M, int r, int c){
    int i, j=0, k=0;

    for(i=0;i<N;i++){
        if(i%2!=0){
            while(V[i]>0){
                V[i]--;
                M[j][k] = V[i-1];
                printf("\t%d ", M[j][k]);
                k++;

                if(k>=c){
                    printf("\n");
                    k=0;
                    j++;
                }
            }
        }
    }
    return;
}

void initializeV(int N, int *V){

    V[0] = 1;
    V[1] = 2;
    V[2] = 17;
    V[3] = 2;
    V[4] = 3;
    V[5] = 1;
    V[6] = 8;
    V[7] = 4;
    V[8] = 6;
    V[9] = 1;
    V[10] = 7;
    V[11] = 3;
    V[12] = 5;
    V[13] = 2;

    return;
}
