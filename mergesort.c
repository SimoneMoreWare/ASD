#include <stdio.h>

void MergeSort(int A[], int B[], int N);
void MergeSortR(int A[], int B[], int l, int r);
void Merge(int A[], int B[], int l, int q, int r);

int main(){
    int A[]={4,3,1,2,5,1,3,6,7,8,1,9,1,2,3,4,56,3,4};
    int B[20];
    for(int i=0;i<19;i++) B[i]=0;
    MergeSort(A,B,19);
    for(int i=0;i<19;i++) printf("%d ",A[i]);
    return 0;
}

void MergeSort(int A[], int B[], int N){
    int l=0,r=N-1;
    MergeSortR(A,B,l,r);
}
void MergeSortR(int A[],int B[], int l, int r){
    int q = (l + r)/2;//indice di mezzo
    if (r <= l)
        return;
    MergeSortR(A, B, l, q);//vettore di sx
    MergeSortR(A, B, q+1, r);//vettore di dx
    Merge(A, B, l, q, r);//unire i vettori quando arrivo al caso base
}

void Merge(int A[],int B[], int l, int q, int r) {
    int i, j, k;
    i = l;//indice inizio sottovettore sx
    j = q+1;//indice inizio sottovettore dx

    for (k = l; k <= r; k++)//da 0 a r

        if (i > q)//esaurisco sottovettore sx
            B[k] = A[j++];
        else if (j > r)//esaurisco sottovettore dx
            B[k] = A[i++];

        else if (A[j]>A[i] || (A[j]> A[i]) )
            B[k] = A[i++];
        else
            B[k] = A[j++];
    for ( k = l; k <= r; k++ )
        A[k] = B[k];
}
