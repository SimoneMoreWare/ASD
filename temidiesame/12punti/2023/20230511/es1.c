#include <stdio.h>
#include <stdlib.h>

void f(int **M,int r,int c,int ***newM);

int main()
{
    int **M;
    int r,c;
    int **newM;
    int i,j;

    printf("Inserisci r: ");
    scanf("%d",&r);
    printf("Inserisci c: ");
    scanf("%d",&c);

    M=malloc(r*sizeof(int*));
    for(i=0;i<r;i++)
        M[i]=malloc(c*sizeof(int));

    printf("Inserisci matrice: \n");
    for(i=0;i<r;i++){
        for(j=0;j<c;j++)
            scanf("%d",&M[i][j]);
    }

    f(M,r,c,&newM);

    for(i=0;i<r;i++){
        for(j=0;j<c;j++){
            printf("%d ",newM[i][j]);
        }printf("\n");
    }

    for(i=0;i<r;i++){
        free(M[i]);
        free(newM[i]);
    }

    free(M);
    free(newM);


    return 0;
}

void f(int **M,int r,int c,int ***newM){
    int i,j,somma,k;

    (*newM)=malloc(sizeof(int*));
    for(i=0;i<r;i++){
       (*newM)[i]=malloc(sizeof(int));
    }

    for(i=0;i<r;i++){
        for(j=0;j<c;j++){
            somma=0;
            if(i!=0){
                k=i;
                for(k=i-1;k>=0;k--)
                    somma=somma+M[k][j];
            }
            if(j!=0){
                k=j;
                for(k=j-1;k>=0;k--)
                    somma=somma+M[i][k];
            }
            (*newM)[i][j]=M[i][j]+somma;
        }
    }



}
