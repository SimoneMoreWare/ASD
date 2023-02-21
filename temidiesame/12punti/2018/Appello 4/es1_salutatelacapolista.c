#include <stdio.h>
#include <stdlib.h>

void displRanking(int C[4][3],int n,int m);

int main(){
    int C[4][3] = {
            {3,1,0},
            {0,1,1},
            {1,1,1},
            {1,1,3}
    };
    int n=4;
    int m=3;
    displRanking(C,n,m);
    return 0;
}
void displRanking(int C[4][3],int n,int m){

    int *squadre = (int *) calloc(n,sizeof(int));
    int *res = (int *) malloc(m*sizeof(int));
    int squadra,giornata;
    int massimopunteggio;
    int i;
    int rmbindex;
    for(giornata=0;giornata<m;giornata++){
        massimopunteggio=0;
        for(squadra=0;squadra<n;squadra++) squadre[squadra] = squadre[squadra] + C[squadra][giornata];

        for(i=0;i<n;i++){
            if(squadre[i]>massimopunteggio){
                massimopunteggio=squadre[i];
                rmbindex=i;
            }
        }
        res[giornata]=rmbindex;
    }
    for(i=0;i<m;i++) printf("%d ",res[i]);
    free(res);
    free(squadre);
}
