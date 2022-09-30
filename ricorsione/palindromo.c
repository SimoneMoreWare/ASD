#include <stdio.h>
#include <string.h>

int palindromo(char s[], int l, int r);

int main(){
    char s[]="abc";
    int res;
    int r=strlen(s)-1;
    int l=0;
    res=palindromo(s,l,r);
    printf("%d\n ",res);
    return 0;
}

int palindromo(char s[],int l,int r){
    int m=(l-r)/2;
    if(l>=r) return 1;
    if(s[l]==s[r]) return palindromo(s,l+1,r-1);
    return 0;
}
