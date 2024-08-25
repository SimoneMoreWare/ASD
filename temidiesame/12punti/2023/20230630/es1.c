#include <stdio.h>
#include <stdlib.h>

void f(int **M,int r,int c,int ***newM);

int main()
{
    int **M;
    int r,c;
    int i,j;
    int **newM;

    printf("Inseerisci r: ");
    scanf("%d",&r);
    printf("Inserisci c: ");
    scanf("%d",&c);

    M=malloc(r*sizeof(int *));
    for(i=0;i<r;i++)
        M[i]=malloc(c*sizeof(int));

    for(i=0;i<r;i++){
        for(j=0;j<c;j++)
            scanf("%d",&M[i][j]);
    }


    f(M,r,c,&newM);



    for(i=0;i<r;i++){
        for(j=0;j<c;j++)
            printf("%d ",newM[i][j]);
        printf("\n");
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
    int i,j,somma,k,t;

    (*newM)=malloc(r*sizeof(int*));
    for(i=0;i<r;i++)
        (*newM)[i]=malloc(c*sizeof(int));


    for(i=0;i<r;i++){
        for(j=0;j<c;j++){
            somma=M[i][j];
            for(k=i+1,t=j+1;k<r && t<c;k++,t++){
            somma=somma+M[k][t];
            }

            //antidiagonale
            for(k=j,t=i;k<i && t>=0;k++,t--)
                if(t>j)
                somma=somma+M[k][t];
            for(k=j-1,t=i+1;k>=0 && t<c;k--,t++)
                if(t>j)
                somma=somma+M[k][t];

            (*newM)[i][j]=somma;

        }
    }




}
