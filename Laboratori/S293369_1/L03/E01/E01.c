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

int majority(int *a, int N){
    return majorityR(a,0,N-1,N/2);
}

int majorityR(int *a,int l,int r,int numberofmajor){
    
    //obiettivo: cercare occorenze dx o sx che sia >N/2 tramite la tecnica dei two pointer
    
    int countSx=0,countDx=0;
    int tmpSx=a[l],tmpDx=a[r];//parcheggio in una variabile gli estremi
    int i=l,j=r;

    if(numberofmajor==0) return a[0]; //nel caso l'array fosse formato da un solo elemento, il maggioritario è l'elemento stesso
    if(l>=r) return -1; //se l indice di sx è uguale o maggiore a quello di destra significa che non ho trovato nessun elemento maggioritario

    //tecnica two pointer
    while(i<=j){
        if (a[i]==tmpDx) countDx++;
        else if (a[i]==tmpSx) countSx++;

        if (a[j]==tmpDx) countDx++;
        else if (a[j]==tmpSx) countSx++;

        i++;
        j--;
    }

    if(countDx>numberofmajor) return tmpDx;
    if(countSx>numberofmajor) return tmpSx;

    return majorityR(a,++l,--r,numberofmajor);//se non trova niente shifto gli estremi
}
