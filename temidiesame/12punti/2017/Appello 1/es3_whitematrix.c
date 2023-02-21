#include <stdio.h>

typedef struct{
    int riga;
    int colonna;
}comando;

void whitematrix_disprip(int pos,int mat[3][3],comando *sol,int n);
int check(int mat[3][3],comando *sol,int n);
int flag=0;

int main(){
    int mat[3][3]={
            {0,1,0},
            {1,0,1},
            {0,1,0}
    };
    int n=3;
    comando sol[3]={{0,0},{0,0},{0,0}};
    whitematrix_disprip(0,mat,sol,n);
    return 0;
}



void whitematrix_disprip(int pos,int mat[3][3],comando *sol,int n){
    int i;
    if(pos>=n){
        //check
        if(check(mat,sol,n)){
            flag=1;
            for(i=0;i<n;i++){
                if(sol[i].riga==1) printf("Riga %d\n",i);
                if(sol[i].colonna==1) printf("Colonna %d\n",i); 
            }
        }
        return;
    }

    if(flag==0){
        sol[pos].riga=1;
        whitematrix_disprip(pos+1,mat,sol,n);
        sol[pos].colonna=1;
        whitematrix_disprip(pos+1,mat,sol,n);
        sol[pos].riga=0;
        whitematrix_disprip(pos+1,mat,sol,n);
        sol[pos].colonna=0;
        whitematrix_disprip(pos+1,mat,sol,n);//MI ERO DIMENTICO DI QUESTA CHIAMATA A CAUSA DEI COPIA INCOLLA, OVVIAMENTE VA MESSA

    }
}

int check(int mat[3][3],comando *sol,int n){
    int i,j,k;
    int matcpy[3][3]; //SI DEVE CREARE UNA COPIA DELLA MATRICE ALTRIMENTI MODIFICHI QUELLA INIZIALE E FAI UN MACELLO, RICORDATELO ANCHE ALL ESAME ANCHE SE SU BLOCCO NOTE

    for(i=0;i<n;i++) for(j=0;j<n;j++) matcpy[i][j]=mat[i][j];

    for(k=0;k<n;k++){
        if(sol[k].riga==1) for(j=0;j<n;j++) matcpy[k][j]= !matcpy[k][j]; //avevo messo al posto di k sol[k].riga, ovviamente non va bene in quanto sol[k].rigaa è 0 o 1 
        if(sol[k].colonna==1) for(i=0;i<n;i++) matcpy[i][k]= !matcpy[i][k]; //avevo messo al posto di k sol[k].colonna, ovviamente non va bene
    }

    for(i=0;i<n;i++) for(j=0;j<n;j++) if(matcpy[i][j]==0) return 0;
    return 1;

}
