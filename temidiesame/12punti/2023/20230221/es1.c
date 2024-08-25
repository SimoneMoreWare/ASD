#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

void f(char **M, int r,int c,char ***newM,int *newR,int *newC);

int main()
{
    char **M;
    int r,c;
    int i,j;
    char **newM;
    int newR=0,newC=0;

    printf("Inserisci r: ");
    scanf("%d",&r);
    printf("Inserisci c: ");
    scanf("%d",&c);

    M=malloc(r*sizeof(char*));
    for(i=0;i<r;i++)
        M[i]=malloc(c*sizeof(char));

    printf("Inserisci M: ");
    for(i=0;i<r;i++)
        for(j=0;j<c;j++)
            scanf("\n%c",&M[i][j]);

    for(i=0;i<r;i++){
        for(j=0;j<c;j++)
            printf("%c ",M[i][j]);
        printf("\n");
    }

    f(M,r,c,&newM,&newR,&newC);

    for(i=0;i<newR;i++){
        for(j=0;j<newC;j++)
            printf("%c ",newM[i][j]);
        printf("\n");
    }

    for(i=0;i<r;i++)
        free(M[i]);
    for(i=0;i<newR;i++)
        free(newM[i]);

    free(M);
    free(newM);

    return 0;
}


void f(char **M, int r,int c,char ***newM,int *newR,int *newC){
    int vett_r[r];
    int vett_c[c];
    int i,j,l,k=0;

    for(i=0;i<r;i++)
        vett_r[i]=0;
    for(j=0;j<c;j++)
        vett_c[j]=0;

    for(i=0;i<r;i++){
        for(j=0;j<c;j++){
            if(M[i][j]=='a' || M[i][j]=='e' || M[i][j]=='i' || M[i][j]=='o' || M[i][j]=='u'){
                vett_c[j]=1;
                vett_r[i]=1;
            }
        }
    }


    for(i=0;i<r;i++){
        if(vett_r[i]==0)
            (*newR)++;
    }
    for(j=0;j<c;j++){
        if(vett_c[i]==0)
        (*newC)++;
    }

    (*newM)=malloc((*newR)*sizeof(char*));
    for(i=0;i<(*newR);i++)
        (*newM)[i]=malloc((*newC)*sizeof(char));

   for(i=0,l=0;i<r;i++){
    if(k!=0)
    l++;
    for(j=0,k=0;j<c;j++){
        if(vett_r[i]==0){
            if(vett_c[j]==0){
            (*newM)[l][k++]=M[i][j];
            }

    }
   }
   }




}
