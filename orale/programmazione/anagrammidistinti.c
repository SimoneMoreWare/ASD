/*
 * Anagrammi distinti di una stringa con caratteri ripetuti
 * (Permutazioni con Ripetizione)
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void permutazioniripetute(int *mark,char *s,char *sol,int pos){
    int i;

    if(pos>=strlen(s)){
        sol[pos]='\0';
        printf("%s\n",sol);
        return;
    }
    for(i=0;i<strlen(s);i++){
        if(mark[i]==0){
            mark[i]=1;
            sol[pos]=s[i];
            permutazioniripetute(mark,s,sol,pos+1);
            mark[i]=0;
        }

    }
}

int main(){
    char s[] = "parola";
    char *sol = (char *) malloc(strlen(s)*sizeof(char));
    int pos=0;
    int *mark = (int *) calloc(strlen(s),sizeof(char));
    permutazioniripetute(mark,s,sol,pos);
    return 0;
}
