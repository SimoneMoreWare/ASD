#include <stdio.h>
#include <stdlib.h>

int maxSubSeq(int *X, int N, int *Y);
int maxSubSeqRic(int pos,int *X,int N,int *sol,int k,int *best_sol,int max,int start);
int main()
{
    int vett[16]={0,8,4,12,2,10,6,14,1,9,5,13,3,11,7,15};
    int N=16;
    int *Y=malloc(sizeof(int));
    int max;

    max=maxSubSeq(vett,N,Y);

    printf("\n\nMax: %d\n",max);




    return 0;
}
/* Cerca la soluzione massima partendo da sequenze lunghe 1 fino a N-1 */
int maxSubSeq(int *X, int N, int *Y){
    int i,max=0;
    int *best_sol=malloc(sizeof(int)); // soluzione a lunghezza massima

    for(i=1;i<N;i++){
        best_sol=realloc(best_sol,i*sizeof(int)); // realloc al posto di malloc
        Y=malloc(i*sizeof(int));
        // tolta inizializzazione a 0

        max=maxSubSeqRic(0,X,N,Y,i,best_sol,max,0);
    }
    // stampa soluzione
    for(i=0;i<max;i++)
        printf("%d ",best_sol[i]);
    return max;
}
/* calcola le combinazioni semplici di k (k<=N) elementi, controlla se sono strettamente
   crescenti e aggiorna o meno il valore massimo e la soluzione migliore */
int maxSubSeqRic(int pos,int *X,int N,int *sol,int k,int *best_sol,int max,int start){
    int i,flag=0;

    // condizione di terminazione
    if(pos>=k){
        /* controllo se strettamente crescente */
        for(i=0;i<k-1 && flag==0;i++){
            if(sol[i]<sol[i+1]){
                flag=0;
            }else{
                flag=1;
            }
        }
        /* se la soluzione è corretta aggiorno il massimo e la soluzione migliore */
        if(flag==0){
            max=k;
            for(i=0;i<k;i++) // cambiato i<N in i<k
                best_sol[i]=sol[i];
        }
        return max;
    }
    for(i=start;i<N;i++){
        sol[pos]=X[i];
        max=maxSubSeqRic(pos+1,X,N,sol,k,best_sol,max,i+1);
    }
    return max;
}
