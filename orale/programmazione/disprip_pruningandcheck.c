/*
 * Scrivere una funzione che, attingendo all’alfabeto,
 * generi tutte le stringhe di 4 lettere tali per cui
 *      la prima e la quarta siano vocali (con la prima alfabeticamente minore della quarta)
 *      mentre la seconda e la terza siano consonanti (con la seconda alfabeticamente maggiore della terza).
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void wrapper(char *alfabeto);
void dispripetute(char *alfabeto,char *consonanti,char *vocali,char *sol,int k,int pos);
int main(){
    char alfabeto[]="qwertyuiopasdfghjklzxcvbnm";
    wrapper(alfabeto);
    return 0;
}

void wrapper(char *alfabeto){
    char consonanti[]="qwrtypsdfghjklzxcvbnm";
    char vocali[]="aeiou";
    char *sol = (char *) malloc(strlen(alfabeto)*sizeof(char));
    int k=4;
    int pos=0;
    dispripetute(alfabeto,consonanti,vocali,sol,k,pos);
    free(sol);
}

void dispripetute(char *alfabeto,char *consonanti,char *vocali,char *sol,int k,int pos){
    int i;
    if(pos>=k){
        sol[pos]='\0';
        if(sol[0]<sol[3] && sol[1]>sol[2]) printf("%s\n",sol);
        return;
    }

    if(pos==0 || pos==3){
        for(i=0;i<strlen(vocali);i++){
            sol[pos]=vocali[i];
            dispripetute(alfabeto,consonanti,vocali,sol,k,pos+1);
        }
    }

    if(pos==1 || pos==2){
        for(i=0;i<strlen(consonanti);i++){
            sol[pos]=consonanti[i];
            dispripetute(alfabeto,consonanti,vocali,sol,k,pos+1);
        }
    }
}
