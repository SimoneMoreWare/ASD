#include <stdio.h>
#include <string.h>
#include <ctype.h>
int countsubstringwith2vocali(char *s,int n);
int isvocale(char c);

int main(){
    char s[] = "forExample";
    int n=4;
    int res;
    res= countsubstringwith2vocali(s,n);
    printf("Numero sottostringhe con due vocali %d",res);
    return 0;
}

int countsubstringwith2vocali(char *s,int n){
    int maxvocali = 2;
    int i,j;
    int countvocali;
    int res=0;

    for(i=0;i<strlen(s)-n+1;i++){
        countvocali=0;
        for(j=i;j<i+n;j++){
            if(isvocale(s[j])==1 && countvocali<2) countvocali++;
        }
        if(countvocali == maxvocali) res++;
    }
    return res;
}

int isvocale(char c){

    char vocali[5] = {'a','e','i','o','u'};
    int i;

    for(i=0;i<5;i++) if(tolower(c) == vocali[i]) return 1;

    return 0;

}
