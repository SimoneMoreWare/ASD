#include <stdlib.h>
#include <stdio.h>

//IL CODICE FA SCHIFO MA CI HO MESSO 3 min per farlo 

/*
 *
 * una funzione riceve due vettori di interi ordinati
 * la funzione alloca un nuovo vettore V3
 * di dimensione opportuna
 *
 * per memorizzare i soli elementi di v1, che non appaiono in v2, conservando l'ordinamento
 * eventuali duplicati di v1, vanno inseriti una sola volta
 *
 * completare il prototipo
 * in modo che v3 e la sua dimensione effettiva siano disponibili al chiamanete
 *
 */

int* f(int v1[6],int v2[2],int dim1,int dim2,int *dim3);

int main(){
    int v1[] = {1,2,2,3,4,5};
    int dim1=6;
    int v2[] = {1,3};
    int dim2=2;
    int i;
    int *v3;
    int dim3;
    v3 = f(v1,v2,dim1,dim2,&dim3);
    printf("dim3 %d\n",dim3);
    for(i=0;i<dim3;i++) printf("%d ",v3[i]);
    free(v3);
    return 0;

}

int* f(int v1[6],int v2[2],int dim1,int dim2,int *dim3){

    int dim_max = dim1-dim2;
    int *res = (int *) malloc(dim_max*sizeof(int));
    int i,j,k;
    j=0;
    k=0;
    for(i=0;i<dim1;i++){
        if(j<dim2){
            if(v1[i]!=v2[j]){
                if(k>0 && v1[i]!=res[k-1]){
                    res[k++]=v1[i];
                }else if(k==0) res[k++]=v1[i];
            }else if(v1[i]==v2[j]){
                j++;
            }
        }else{
            if(k>0 && v1[i]!=res[k-1]){
                res[k++]=v1[i];
            }
            else if(k==0) res[k++]=v1[i];
        }

    }
    (*dim3)=k;
    return res;

}
