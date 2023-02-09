/*
 * Scrivere una funzione che partendo da un vettore di numeri interi
 * ponga i numeri pari
 * e quelli dispari
 * in due nuovi vettori allocati dinamicamente
 * ed infine ritorni i due vettori al programma chiamante.
 */

#include <stdio.h>
#include <stdlib.h>
void f(int *V,int N,int **V1,int **V2,int *index_pari,int *index_dispari);
int main(){
    int V[] = {1,5,6,8,3,7,9,2,8,3,9,0,12};
    int N = 13;
    int *V1,*V2;
    int i;
    int index_pari=0;
    int index_dispari=0;
    f(V,N,&V1,&V2,&index_pari,&index_dispari);
    for(i=0;i<index_pari;i++) printf("%d ",V1[i]);
    printf("\n");
    for(i=0;i<index_dispari;i++) printf("%d ",V2[i]);
    return 0;
}

void f(int *V,int N,int **V1,int **V2,int *index_pari,int *index_dispari){
    (*V1) = (int *) malloc(N*sizeof(int));
    (*V2) = (int *) malloc(N*sizeof(int));
    int i;
    for(i=0;i<N;i++){
        if(V[i]%2==0){
            (*V1)[(*index_pari)++]=V[i];
        }else{
            (*V2)[(*index_dispari)++]=V[i];
        }
    }
}
