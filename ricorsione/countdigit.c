#include <stdio.h>

int countdigit(int n);

int main(){
    int n=123,res;
    res=countdigit(n);
    printf("%d ",res);
    return 0;
}

int countdigit(int n){
    if(n==0) return 0;
    return countdigit(n/10)+1;
}
