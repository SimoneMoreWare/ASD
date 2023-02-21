#include <stdio.h>
#include <stdlib.h>

void f(int V[10],int N);

int main() {
    int V[] = {1,0,2,0,3,0,5,0,6,0};
    int N=10;
    f(V,N);
    return 0;
}

void f(int V[10],int N){

    int i,j;
    int *tmp = (int *) malloc(N*sizeof(int));
    int sequenza=0;
    int sequenzamax = 0;
    int k=0;
    int t=0;

    for(i=0;i<N;i++){
        if(V[i] != 0){
            sequenza++;
        }else{

            if(sequenza==sequenzamax) for(j=i-sequenzamax;j<i;j++) tmp[k++]=V[j];

            if(sequenza>sequenzamax){
                k=0;
                sequenzamax=sequenza;
                for(j=i-sequenzamax;j<i;j++) tmp[k++]=V[j];
            }

            sequenza=0;
        }
    }

    //se tutto il vettore non contiene 0 allora lo carico dopo aver ciclato il for
    if(sequenza==sequenzamax) for(j=i-sequenzamax;j<i;j++) tmp[k++]=V[j];
    if(sequenza>sequenzamax){
        k=0;
        sequenzamax=sequenza;
        for(j=i-sequenzamax;j<i;j++) tmp[k++]=V[j];
    }

    for(i=0;k!=0 && sequenzamax!=0 && i<k/sequenzamax;i++){
        for(j=0;j<sequenzamax;j++) printf("%d ",tmp[t++]);
        printf("\n");
    }

    free(tmp);
}
