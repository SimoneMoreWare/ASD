#include <stdio.h>
#include <stdlib.h>

void invertSequence(int *v1,int n,int *v2);

int main(){
    int n=11;
    int v1[]={1,2,3,4,5,0,12,1,13,14,2};
    int *v2=(int*) malloc(n*sizeof(int));
    invertSequence(v1,n,v2);
    for(int i=0;i<n;i++) printf("%d ",v2[i]);
    free(v2);
    return 0;
}


void invertSequence(int *v1,int n,int *v2){
    int *tmp;
    int i,j;
    int c=0;
    int k=0;
    tmp=(int *) malloc(n*sizeof(int));
    for(i=0;i<n;i++){
        if(i==n-1){

        }
        if(v1[i]<v1[i+1]){
            tmp[c++]=v1[i];
        }else{
            //si interrompe la sequenza crescete
            tmp[c]=v1[i]; //salvo l'ultimo elemento che ho considerato, sarà colui che termina la sequenza crescente;
            if(c==0) v2[k++]=tmp[c];
            else for(j=c;j>=0;j--) v2[k++]=tmp[j];
            c=0;
        }
    }
    //considero ultimo elemento
    tmp[c]=v1[n-1];
    if(c==0) v2[k++]=tmp[c];
    else for(j=c;j>=0;j--) v2[k++]=tmp[j];

}
