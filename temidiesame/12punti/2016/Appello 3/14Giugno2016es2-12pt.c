#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LENGTH 1000

int separaParole(char frase[MAX_LENGTH], char ***parole);

int main()
{
    char frase[MAX_LENGTH] = "Ciao a tutti come state";
    char **parole;
    int n,i;

    n = separaParole(frase,&parole);

    for (i=0; i<n; i++)
        printf("parola %d -> %s\n", i, parole[i]);

    printf("\nParole totali: %d", n);

    return 0;
}

int separaParole(char frase[MAX_LENGTH], char ***parole){
    int i,count=0,index = -1,j=0;
    char parolaCorrente[MAX_LENGTH]="",**p;

    //primo ciclo per contare il numero di parole
    for(i=0;frase[i]!='\0';i++){
        if(frase[i]==' ')
            count++;
    }
    count++;

    p = malloc(count*sizeof(char *));

    for(i=0;frase[i]!='\0';i++){
        if(frase[i]!=' '){
            parolaCorrente[j] = frase[i];
            j++;
        }else{
            index++;
            parolaCorrente[j] = '\0';
            p[index] = strdup(parolaCorrente);
            strcpy(parolaCorrente,"");
            j=0;
        }
    }
    index++;
    parolaCorrente[j] = '\0';
    p[index] = strdup(parolaCorrente);
    strcpy(parolaCorrente,"");

    *parole = p;

    return count;
}
