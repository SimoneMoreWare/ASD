/*
Se conosciamo l'elemento maggioritario nelle metà sinistra e destra di un array, possiamo determinare quale è l'elemento maggioritario 

approccio divide et impera
si ricorre nelle metà sinistra e destra di un array fino a quando non è possibile ottenere un caso base,
in questo caso array di lunghezza 1, l'elemento maggioritario è banalmente il suo unico elemento, 
// quindi la ricorsione si ferma qui. 

Se il sottoarray corrente è più lungo di lunghezza-1, 
dobbiamo combinare le risposte per le metà sinistra e destra. 
Se sono d'accordo sull'elemento maggioritario, l'elemento maggioritario per la array complessiva è ovviamente lo stesso. 
Se non sono d'accordo, solo uno di loro può essere "giusto", quindi dobbiamo contare le occorrenze degli elementi sinistro e destro 
per determinare quale risposta della sottosezione è globalmente corretta. 
*/


#include <stdio.h>
#include <stdlib.h>

int majority( int *a, int N);
int majorityR( int *a, int l,int r,int numberofmajor);

int main(){
    int N,i,res;
    int *v;

    printf("inserisci dim: ");
    scanf("%d",&N);
    v=(int *) malloc(N*sizeof(int));

    for(i=0;i<N;i++){
        scanf("%d",v+i);
    }

    res= majority(v,N);

    if(res!=-1){
        printf("elemento maggioritario: %d",res);
    }else{
        printf("nessun elemento maggioritario");
    }

    free(v);
    return 0;

}

int majorityElement(int* nums, int numsSize){
    return majorityR(nums,0,numsSize-1);
}

int majorityR(int *a,int l,int r){
   
    int m=(r-l)/2+l;
    int left,right;
    int leftCount,rightCount;
     //caso base: ho un solo elemento ed è per definizione maggioritario
    if(l==r) return a[l];
    
    //per ricorsione procedo nel sottovettore sx e dx, spaccato a metà
    left=majorityR(a,l,m);
    right=majorityR(a,m+1,r);
    
    //se le due metà hanno lo stesso maggiorante ritorna left
    if(left==right) return left;
    
    //altrimenti conta ogni elemento e trova risultato.
    leftCount=countInRange(a,left,l,r);
    rightCount=countInRange(a,right,l,r);
    
    return leftCount > rightCount ? left : right;
    
    
}

int countInRange(int a[], int num, int l, int r) {
        int count = 0;
        for (int i = l; i <= r; i++) {
            if (a[i] == num) {
                count++;
            }
        }
        return count;
}


