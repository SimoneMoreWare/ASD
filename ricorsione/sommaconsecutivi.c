#include <stdio.h>

int somma_consecutivi_ricorsiva(int n);

int main(){
    int n=4,res;
    res=somma_consecutivi_ricorsiva(n);
    printf("%d\n",res);
    return 0;
}

int somma_consecutivi_ricorsiva(int n){
    if(n==1) return 1;
    return n+somma_consecutivi_ricorsiva(n-1);
}
