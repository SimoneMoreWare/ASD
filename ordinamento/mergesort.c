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

void MergeSort(int A[],int B[],int N){
    int l=0,r=N-1; //indici
    MergeSortR(A,B,l,r);
}

void MergeSortR(int A[],int B[],int l,int r){
    int q=(l+r)/2; //indice di mezzo, in questo modo definsico vettore di sx e dx
    if(l>=r) return; //se l'indice sx supera o raggiunge quello destro mi fermo
    MergeSortR(A,B,l,q);//mergesort sul sottovettore sx
    MergeSortR(A,B,q+1,r);//mergesort sul sottovettore dx
    Merge(A,B,l,q,r);//fusione
}

void Merge(int A[],int B[],int l,int q,int r){
    int i,j,k;
    i=l; //inizio sottovettore sx
    j=q+1; //inizio sottovettore dx

    for(k=l;k<=r;k++){
        if(i>q){//sottovettore sx terminato, uso l indice del sottovettore dx e riempo sottovettore dx
            B[k]=A[j++];
        }else if(j>r){//sottovettore dx terminato e riempo il sottovettore sx, uso l'indice del sottovettore sx
            B[k]=A[i++];
        }else if(A[j]>A[i]){ //se a[j]>[i] ricopiare a[i] in B e avanzare i (j resta invariato)
          B[k]=A[i++];
        }else{ //altrimenti ricopiare a[j] in b e avanzare j, i resta invariato
            B[k]=A[j++];
        }
    }
    for(k=l;k<=r;k++) A[k]=B[k];
}
