#include <stdio.h>
#include <stdlib.h>

int main(){
    int dim;
    int *parray;
    int i;
    printf("Inserisci dimensione ");
    fflush(stdin);
    scanf("%d",&dim);
    parray=(int *) malloc(dim*sizeof(int));

    //caricamento vettore
    for(i=0;i<dim;i++){
        *(parray+i)=i;
    }

    //output
    for(i=dim-1;i>=0;i--){
        printf("%d ",*(parray+i));
    }
    return 0;
}
