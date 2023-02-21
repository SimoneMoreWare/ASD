#include <stdio.h>
#include <string.h>
#include <stdlib.h>


int isPresent(char temp[1000], char ***parole, int n){

    if (n==0) return 1 ;

    int i ;

    for (i = 0 ; i < n; i++){
        if(strncmp((*parole)[i],temp,strlen((*parole)[i]))==0)
        return 0;
    }

    return 1;
}




int separaParole(char frase, char **parole){

    char *temp;
    int n = 0;
    temp=strtok(frase," ");

    while(temp!=NULL){

        if (isPresent(temp,parole,n)==1) (*parole)[n++] = strdup(temp);

        temp= strtok(NULL," ");
    }


    return n;



}














int main() {
    char frase[1000], **parole;
    int n,i;
    parole = malloc((strlen(frase)/2)(sizeof(char)));

    strcpy(frase,"ciao come stai ciao");
    n=separaParole(frase,&parole);

    for(i=0;i<n;i++) printf("parola %d -> %s\n",i,parole[i]);

    return 0;
}
