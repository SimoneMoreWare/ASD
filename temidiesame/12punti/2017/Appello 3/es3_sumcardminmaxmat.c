#include <stdio.h>
#include <stdlib.h>

void f(int mat[5][2],int r,int c,int k);
void powerset_combsemplici(int pos,int start,int mat[5][2],int r,int c,int *sol,int sommarichiesta,int k,int *cardinalitamassima,int *cardinalitaminima,int *sumcardmin,int *sumcardmax);

int main(){
    int mat[5][2]={
            {6,1},
            {8,314},
            {64,24},
            {21,75},
            {54,589},
    };
    int r=5;
    int c=2;
    int k=22;
    f(mat,r,c,k);
    return 0;
}

void f(int mat[5][2],int r,int c,int k){
    int pos=0;
    int start=0;
    int *sol = (int *) malloc((r*c)*sizeof(int));
    int i;
    int cardinalitaminima = r*c+1;
    int cardinalitamassima = 0;
    int *sumcardmin = (int *) malloc((r*c)*sizeof(int));
    int *sumcardmax = (int *) malloc((r*c)*sizeof(int));
    for(i=1;i<=(r*c);i++) powerset_combsemplici(pos,start,mat,r,c,sol,k,i,&cardinalitamassima,&cardinalitaminima,sumcardmin,sumcardmax);

    if(cardinalitaminima == ((r*c)+1)){
        printf("non ci sono sottoinsiemi di cardinalità mininima\n");
    }else{
        printf("(");
        for(i=0;i<cardinalitaminima;i++) printf("%d ",sumcardmin[i]);
        printf(")");
        printf(" %d\n",k);
    }

    if(cardinalitamassima==0){
        printf("non ci sono sottoinsiemi di cardinalita massima\n");
    }else{
        printf("(");
        for(i=0;i<cardinalitamassima;i++) printf("%d ",sumcardmax[i]);
        printf(")");
        printf(" %d\n",k);
    }

    free(sol);
    free(sumcardmin);
    free(sumcardmax);
}

void powerset_combsemplici(int pos,int start,int mat[5][2],int r,int c,int *sol,int sommarichiesta,int k,int *cardinalitamassima,int *cardinalitaminima,int *sumcardmin,int *sumcardmax){

    int i,j;
    int riga,colonna;
    int sommapartial;
    if(pos>=k){
        sommapartial=0;
        for(i=0;i<k;i++) sommapartial=sommapartial+sol[i];
        if(sommapartial==sommarichiesta){
            if(k<(*cardinalitaminima)){
                (*cardinalitaminima)=k;
                for(j=0;j<k;j++) sumcardmin[j]=sol[j];
            }
            if(k>=(*cardinalitamassima)){
                (*cardinalitamassima)=k;
                for(j=0;j<k;j++) sumcardmax[j]=sol[j];
            }
        }
        return;
    }

    for(i=start;i<(r*c);i++){
        riga= i/c;
        colonna = i%c;
        sol[pos] = mat[riga][colonna];
        powerset_combsemplici(pos+1,i+1,mat,r,c,sol,sommarichiesta,k,cardinalitamassima,cardinalitaminima,sumcardmin,sumcardmax);
    }
}
