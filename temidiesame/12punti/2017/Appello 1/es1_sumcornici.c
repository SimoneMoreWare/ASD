#include <stdio.h>
#include <stdlib.h>
void sommaCornici(int mat[5][5], int N, int **vet){
    //si hanno n/2+1 cornici
    int i,j,k;
    int start_riga;
    int start_colonna;
    int ncornici=(N/2)+1;
    *vet=(int *) malloc(ncornici*sizeof(int));
    int sum;
    for(k=0;k<ncornici;k++){
        sum=0;
        start_riga=k;
        start_colonna=k;
        if(start_colonna==N-k-1) sum=mat[N-k-1][N-k-1];
        else{
            for(j=start_colonna;j<N-k;j++){
                printf("%d %d\n",mat[start_riga][j],mat[N-start_riga-1][j]);
                sum=sum+mat[start_riga][j];
                sum=sum+mat[N-start_riga-1][j];
            }

            for(i=start_riga+1;i<N-k-1;i++){
                printf("col %d %d\n",mat[i][start_colonna],mat[i][N-start_colonna-1]);
                sum=sum+mat[i][start_colonna];
                sum=sum+mat[i][N-start_colonna-1];
            }
        }

        (*vet)[k]=sum;
    }
}
int main(){
    int mat[5][5]={
            {1,2,3,4,5},
            {6,7,8,9,0},
            {1,2,3,4,5},
            {6,7,8,9,0},
            {1,1,1,1,1}
    };
    int N=5;
    int *vet;
    sommaCornici(mat,N,&vet);
    for(int i=0;i<N/2+1;i++) printf("%d ",vet[i]);
    return 0;
}
