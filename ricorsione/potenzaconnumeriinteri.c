#include <stdio.h>

int potenza(int n,int k);

int main(){
    int n=3,k=4,res;
    res=potenza(n,k);
    printf("%d\n ",res);
    return 0;
}

int potenza(int n,int k){
    if(k==1) return n;
    return potenza(n,k-1)*n;
}
