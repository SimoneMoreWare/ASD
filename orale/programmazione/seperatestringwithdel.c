#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int main(){
    char s[]="ciao.a.tutti";
    int dim=1;
    char del='.';
    int i;
    char **res;
    for(i=0;s[i]!='\0';i++) if(s[i]==del) dim++;

    res=(char **) malloc(dim*sizeof(int));
    for(i=0;i<dim;i++) res[i] = (char *) malloc(strlen(s)*sizeof(char));
    int k=0;
    int t=0;
    for(i=0;s[i]!='\0';i++){
        if(s[i]!=del){
            res[t][k++]=s[i];
        }else{
            res[t][k]='\0';
            k=0;
            t++;
        }
    }
    res[t][k]='\0';

    for(i=0;i<dim;i++) printf("%s\n",res[i]);
    for(i=0;i<dim;i++) free(res[i]);
    free(res);
    return 0;
 }
