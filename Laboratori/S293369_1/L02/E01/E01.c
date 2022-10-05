#include <stdio.h>

int gcd(int a,int b);

int main(){
    int a=39,b=65,res;
    res=gcd(a,b);
    printf("%d",res);
    return 0;
}

int gcd(int a,int b){
    int tmp;
    if(a<b){
        tmp=a;
        a=b;
        b=tmp;
    }
    if(b==1) return 1;
    if(b==0) return a;
    if(a%2==0 && b%2==0) return 2*gcd(a/2,b/2);
    if(a%2!=0 && b%2==0) return gcd(a,b/2);
    if(a%2==0 && b%2!=0) return gcd(b,a/2);
    if(a%2!=0 && b%2!=0) return gcd((a-b)/2,b);
}
