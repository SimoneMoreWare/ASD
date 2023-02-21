#include <stdio.h>
#include <stdlib.h>

void rotazioneadestra(int *array,int N,int D);

int main(){
    int N=10;
    int D=3;
    int array[]={5,4,10,-1,7,20,11,-3,6,34};
    rotazioneadestra(array,N,D);
    for(int i=0;i<N;i++) printf("%d ",array[i]);
    return 0;
}

void rotazioneadestra(int *array,int N,int D){
    int *vettoretmp;
    int i,k=0;
    int l=N-1;
    vettoretmp=(int *) malloc(D*sizeof(int));
    for(i=N-D;i<N;i++) vettoretmp[k++]=array[i];
    for(i=N-D-1;i>=0;i--) array[l--]=array[i];
    for(i=0;i<D;i++) array[i]=vettoretmp[i];
}
