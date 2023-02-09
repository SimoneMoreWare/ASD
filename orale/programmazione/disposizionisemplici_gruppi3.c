/*
 * dato un vettore contenente tutte le lettere (una sola volta),
 * genera una stringa di dimensione 3,
 * dove le prime due lettere sono vocali e l'ultima è una consonante,
 * la seconda vocale deve essere maggiore della prima
 */

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

void wrapper(char *lettere);
void disposizionisemplici(char *sol,char *lettere,int pos,char *vocali,char *consonanti,int k);

int main(){
    char lettere[] = "qwertyuiopasdfghjklzxcvbnm";
    wrapper(lettere);
    return 0;
}

void wrapper(char *lettere){
    char *sol = (char *) malloc(strlen(lettere)*sizeof(char));
    int pos = 0;
    int k=3;
    char vocali[] = "aeiou";
    char consonanti[] = "qwrtypsdfghjklmnbvcxz";
    disposizionisemplici(sol,lettere,pos,vocali,consonanti,k);
    free(sol);
}

void disposizionisemplici(char *sol,char *lettere,int pos,char *vocali,char *consonanti,int k){
    int i;
    if(pos>=k){
        sol[pos]='\0';
        printf("%s\n",sol);
        return;
    }

    if(pos<=1){
        for(i=0;i<strlen(vocali);i++){
            if((pos==0) || (pos==1 && vocali[i]>sol[0])){
                sol[pos]=vocali[i];
                disposizionisemplici(sol,lettere,pos+1,vocali,consonanti,k);
            }
        }
    }
    if(pos==2){
        for(i=0;i<strlen(consonanti);i++){
            sol[pos]=consonanti[i];
            disposizionisemplici(sol,lettere,pos+1,vocali,consonanti,k);
        }
    }


}
