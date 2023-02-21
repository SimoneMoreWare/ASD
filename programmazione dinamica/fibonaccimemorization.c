#include <stdio.h>
#include <stdlib.h>
int fibonacci(int n,int *memoization);
int main(){
    int n;
    int *memoization;
    printf("Inserisci quanti numeri di fibonacci vuoi calcolare ");
    scanf("%d",&n);
    memoization=(int *) calloc(n,sizeof(int));
    fibonacci(n,memoization);
    for(int i=0;i<n;i++){
        printf("%d ",memoization[i]);
    }
    return 0;
}
int fibonacci(int n, int *memoization){
    if(n==0 || n==1){
        memoization[n]=1;
        return 1;
    }
    if(memoization[n]!=0) return memoization[n];
    memoization[n]=fibonacci(n-1,memoization) + fibonacci(n-2,memoization);
    return memoization[n];
}
