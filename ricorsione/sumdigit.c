#include <stdio.h>

int sumdigit(int n);

int main(){
    int n=19,res;
    res=sumdigit(n);
    printf("%d ",res);
    return 0;
}

int sumdigit(int n){
    if(n==0) return n%10;
    return(sumdigit(n/10)+n%10);
}
