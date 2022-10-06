#include <stdio.h>
#include <string.h>
void ordina(char **ptrchat,int dim);
void binarysearch(char **ptrchat,int dim,int start,int end,char prefix[],int lenprefix);
int main(){
    char chat[][15]={
        "lunedi",
        "martedi",
        "mercoledi",
        "giovedi",
        "venerdi",
        "sabato",
        "domenica"
    };
    char prefix[]="martedi";
    int lenprefix=strlen(prefix);
    int start=0;
    int end=6;
    char *ptrchat[15];
    for(int i=0;i<7;i++){
        ptrchat[i]=&chat[i];
    }
    ordina(ptrchat,7);
   
    binarysearch(ptrchat,7,0,7-1,prefix,lenprefix);
    return 0;
}

void ordina(char **ptrchat,int dim){
    char *tmp;
    int i,j;
   
    for(i=1;i<dim;i++){
        tmp=ptrchat[i];
        j=i-1;
        while(j>=0 && strcmp(tmp,*(ptrchat+j))<0){
            ptrchat[j+1]=ptrchat[j];
            j--;
        }
        ptrchat[j+1]=tmp;
    }
    
}

void binarysearch(char **ptrchat,int dim,int start,int end,char prefix[],int lenprefix){
    int m=(start+end)/2;
    if(strncmp(prefix,*(ptrchat+m),lenprefix)==0){
        printf("%s ",*(ptrchat+m));
        return;
    }
    if(strncmp(prefix,*(ptrchat+m),lenprefix)<0) return binarysearch(ptrchat,dim,start,m,prefix,lenprefix);
    if(strncmp(prefix,*(ptrchat+m),lenprefix)>0) return binarysearch(ptrchat,dim,m,end,prefix,lenprefix);
}
