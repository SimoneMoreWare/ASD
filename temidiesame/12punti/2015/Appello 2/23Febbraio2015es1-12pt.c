#include <stdio.h>
#include <stdlib.h>
#define N 10

void InvertSequence(int *v1, int n, int *v2);

int main()
{
    int v1[N] = { 1, 2, 3, 4, 5, 0, 12, 13, 14, 2}, v2[N],i;

    InvertSequence(v1,N,v2);

    printf("v2 after InvertSequence:\n\t");

    for(i=0; i<N; i++){
        printf(" %d ", v2[i]);
    }

    return 0;
}

void InvertSequence(int *v1, int n, int *v2){
    int i = 0,j,k;

    while(i<n){
        j=i;

        while(v1[j]<v1[j+1] && j+1<n){
            j++;
        }

        for(k=i; k<=j; k++){
            v2[k]=v1[j-k+i];
        }
        i=j+1;
    }

    return;
}
