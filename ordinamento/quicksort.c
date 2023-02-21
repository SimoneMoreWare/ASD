#include <stdio.h>

void quicksort(int array[],int l,int r);
int partition(int array[],int l,int r);


int main(){
    int array[]={13,7,8,1,2,8,5,3,11,4};
    int l=0,r=9; 
    quicksort(array,l,r);
      for(int i=0;i<=r;i++) printf("%d ",array[i]);

    return 0;
}

int partition(int array[],int l,int r){
    int tmp;
    int pivot=array[r]; //prendo come pivot l'ultimo elemento
    int i=l-1; //prendo indice i e lo posiziono alla sx
  
    for(int j=l;j<r;j++){
      if(array[j]<=pivot){
        i++;
        tmp=array[j];
        array[j]=array[i];
        array[i]=tmp;
      }
    }
  
    tmp=array[i+1];
    array[i+1]=array[r];
    array[r]=tmp;
               
    return i+1;
}

void quicksort(int array[],int l,int r){
    int q;
    if(l<r){
      q=partition(array,l,r);
      quicksort(array,l,q-1);
      quicksort(array,q+1,l);
    }
}
