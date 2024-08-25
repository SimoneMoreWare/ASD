#include <stdio.h>
#include <stdlib.h>

void f(int **M,int r,int c, float ***newM);
int main()
{
    int **M;
    float **newM;
    int r,c;
    int i,j;

    printf("Inserire r: ");
    scanf("%d",&r);
    printf("Inserire c: ");
    scanf("%d",&c);

    M=malloc(r*sizeof(int*));
    for(i=0;i<r;i++)
        M[i]=malloc(c*sizeof(int));

    printf("Inserisci matrice\n");
    for(i=0;i<r;i++){
        for(j=0;j<c;j++)
            scanf("%d",&M[i][j]);
    }

    f(M,r,c,&newM);

    for(i=0;i<r;i++){
        for(j=0;j<c;j++)
            printf("%.2f ",newM[i][j]);
        printf("\n");
    }

    return 0;
}

void f(int **M,int r,int c, float ***newM){
    int i,j;
    float somma=0,cnt=0;

    (*newM)=malloc(r*sizeof(int*));
    for(i=0;i<r;i++)
        (*newM)[i]=malloc(c*sizeof(int));

    for(i=0;i<r;i++){
        for(j=0;j<c;j++){
            somma=M[i][j];
            cnt=1;
            if(j!=0){
                somma=somma+M[i][j-1];
                cnt++;}
            if(j+1<c){
                somma=somma+M[i][j+1];
                cnt++;}
            if(i!=0){
                somma=somma+M[i-1][j];
                cnt++;
                if(j!=0){
                somma=somma+M[i-1][j-1];
                cnt++;}
                if(j+1<c){
                somma=somma+M[i-1][j+1];
                cnt++;}
                }
            if(i+1<r){
                somma=somma+M[i+1][j];
                cnt++;
                if(j!=0){
                somma=somma+M[i+1][j-1];
                cnt++;}
                if(j+1<c){
                somma=somma+M[i+1][j+1];
                cnt++;}
                }
            (*newM)[i][j]=(float)(somma/cnt);

        }
    }

}
