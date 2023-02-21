#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void eraseDuplicate(char *str);

int main(){
    char str[]="aa;;;bbbab;";
    eraseDuplicate(str);
    printf("%s",str);
    return 0;
}

void eraseDuplicate (char *str){
    int i,j;
    int flag;
    char *res=(char *) malloc((strlen(str))*sizeof(char));
    strcpy(res,""); //mi sono dimenticato di inizializzare stringa vuota
    for(i=0;i<strlen(str);i++){
        flag=1;
        for(j=0;j<strlen(res);j++) if(str[i]==res[j]) flag=0;
        if(flag==1)  sprintf(res+strlen(res),"%c",str[i]); // mi sono dimenticato strlen(res)
    }
    strcpy(str,res);
}
