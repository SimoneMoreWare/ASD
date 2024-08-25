#include <stdio.h>
#include <stdlib.h>

void f(int **M,int r,int c,int k,int ***newM);

int main()
{
    int **M;
    int r,c,k;
    int i,j;
    int **newM;
    printf("Inserisci r: ");
    scanf("%d",&r);
    printf("Inserisci c: ");
    scanf("%d",&c);

    M=malloc(r*sizeof(int *));
    for(i=0;i<r;i++)
        M[i]=malloc(r*sizeof(int));

    printf("Inserisci matrice:\n");
    for(i=0;i<r;i++){
        for(j=0;j<c;j++)
            scanf("%d",&M[i][j]);
    }

    printf("Inserisci k: ");
    scanf("%d",&k);

    f(M,r,c,k,&newM);

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


void f(int **M,int r,int c,int k,int ***newM){
    int i,j;
    int cnt,somma,t;

    (*newM)=malloc(r*sizeof(int *));
    for(i=0;i<r;i++){
        (*newM)[i]=malloc(c*sizeof(int));
    }


    for(i=0;i<r;i++){
        for(j=0;j<c;j++){
        somma=0;
        cnt=0;
            for(t=j+1;cnt<k && t<c;t++){
                somma=somma+M[i][t];
                cnt++;
            }
        cnt=0;
            for(t=j-1;cnt<k && t>=0;t--){
                somma=somma+M[i][t];
                cnt++;
            }
        cnt=0;
        for(t=i+1;t<r && cnt<k;t++){
            somma=somma+M[t][j];
            cnt++;
        }
        cnt=0;
        for(t=i-1;t>=0 && cnt<k;t--){
            somma=somma+M[t][j];
            cnt++;
        }

        (*newM)[i][j]=somma;

        }

    }


}
