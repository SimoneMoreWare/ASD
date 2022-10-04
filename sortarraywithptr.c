#include <stdio.h>
#include <stdlib.h>

void sort_arrayofpointer(int **arraypointer,int arraySize);

int main(){
    int array[]={5,6,4,8,2,3,1};
    int arraySize=7;
    int *arrayofpointer[10];//MAXN
    int i;
    for(i=0;i<arraySize;i++) arrayofpointer[i]=&array[i];
    sort_arrayofpointer(arrayofpointer,arraySize);
    printf("\n");
    for(i=0;i<arraySize;i++) printf("%d ",array[i]);
    printf("\n");
    for(i=0;i<arraySize;i++) printf("%d ",*arrayofpointer[i]);

    return 0;
}

void sort_arrayofpointer(int **arraypointer,int arraySize){
    int i,j;
    int *tmp;
    for(i=1;i<arraySize;i++){
        tmp=arraypointer[i];
        j=i-1;
        while(j>=0 && *tmp<*(arraypointer[j])){
            arraypointer[j+1]=arraypointer[j];
            j--;
        }
        (arraypointer[j+1])=tmp;
    }
    for(i=0;i<arraySize;i++){
        printf("%d ",*arraypointer[i]);
    }
}
