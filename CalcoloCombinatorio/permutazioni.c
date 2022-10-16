#include <stdio.h>
#include <stdlib.h>

#define filename "../brani.txt"

void permutazioni(int *array,int dim);
int permutazioniR(int *array,int *mark,int *sol,int pos,int dim, int cnt);

int main(){
    FILE *fpin;
    int dim;
    int *array;
    int i;
    fpin=fopen(filename,"r");
    if(fpin!=NULL){
        fscanf(fpin,"%d",&dim);
        array=(int *) malloc(dim*sizeof(int));
        for(i=0;i<dim;i++){
            fscanf(fpin,"%d",&array[i]);
        }
        permutazioni(array,dim);
        free(array);
    }else{
        printf("Erorre file");
    }
}

void permutazioni(int *array,int dim) {
    int pos = 0, *mark, *sol, i,res,cnt=0;
    mark=(int *) malloc(dim*sizeof(int));
    sol=(int *) malloc(dim*sizeof(int));
    for (i = 0; i < dim; i++) mark[i] = 0;
    res=permutazioniR(array,mark,sol,pos,dim,cnt);
    printf("%d ",res);
}

int permutazioniR(int *array,int *mark,int *sol,int pos,int dim, int cnt){
    int i;
    if(pos>=dim){
        for(i=0;i<dim;i++) printf("%d ",sol[i]);
        printf("\n");
        return cnt+1;
    }
    for(i=0;i<dim;i++){
        if(mark[i]==0){
            mark[i]=1;
            sol[pos]=array[i];
            cnt=permutazioniR(array,mark,sol,pos+1,dim,cnt);
            mark[i]=0;
        }
    }
    return cnt;
}
