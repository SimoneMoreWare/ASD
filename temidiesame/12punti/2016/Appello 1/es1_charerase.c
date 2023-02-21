/*
La funzione charErase prende in ingresso due parametri: una stringa di caratteri (str) e un array di interi (pos).

La funzione alloca due nuove stringhe di caratteri, res e tmp, entrambe della stessa lunghezza di str.

La funzione copia il contenuto della stringa str nella stringa tmp con la funzione strcpy.

Successivamente, la funzione itera sull'array di interi pos finché il suo valore non è -1. In ogni iterazione, sostituisce il carattere nella posizione indicata da pos[k] nella stringa tmp con uno spazio.

Dopo il ciclo, la funzione copia una stringa vuota nella stringa res e itera sulla stringa tmp. Ogni volta che incontra un carattere diverso da uno spazio, lo concatena alla stringa res con la funzione sprintf.

Alla fine, la funzione restituisce la stringa res.
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char *charErase(char *str,int *pos);

int main(){
    char str[]="ThisIsAString";
    int pos[]={7,4,2,0,11,-1};
    char *res;
    res= charErase(str,pos);
    printf("%s",res);
    return 0;
}

char *charErase(char *str,int *pos){
    char *res=(char *) malloc((strlen(str))*sizeof(char));
    char *tmp=(char *) malloc((strlen(str))*sizeof(char));
    int k=0;
    strcpy(tmp,str);
    while(pos[k]!=-1){
        tmp[pos[k]]=' ';
        k++;
    }
    //printf("%s ",tmp);
    strcpy(res,"");
    for(int i=0;i<strlen(tmp);i++){
        if(tmp[i]!=' ') sprintf(res+strlen(res),"%c",tmp[i]);
    }
    return res;
}
