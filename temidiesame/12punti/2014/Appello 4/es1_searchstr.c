#include <stdio.h>
#include <string.h>

void searchStr(char *str,int *start,int *len);

int main(){
    char str[]="abcf";
    int start;
    int len;
    searchStr(str,&start,&len);
    printf("%d %d",start,len);
    return 0;
}

void searchStr(char *str,int *start,int *len){
    //rintraccia sequenza di caratteri uguali di lunghezza maggiore, ritornando l'indice di inizio in start e lunghezza in len

    int i;

    *start=0;
    *len=1;
    int lenpartial=1;
    int startpartial;
    int flagstart=1;

    for(i=0;i<strlen(str)-1;i++){
        if(str[i]==str[i+1]){
            lenpartial++;
            if(flagstart==1){
                startpartial=i;
                flagstart=0;
            }
            if(lenpartial>(*len)){
                (*len)=lenpartial;
                (*start)=startpartial;
            }
        }else{
            lenpartial=1;
            flagstart=1;
        }
    }

}
