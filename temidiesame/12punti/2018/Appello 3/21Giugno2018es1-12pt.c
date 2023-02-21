#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int subString(char *s, int n);
int main()
{
    char s[10]="forExample";
    int n=4,sol;

    sol=subString(s,n);

    printf("Soluzioni: %d\n",sol);

    return 0;
}
/* calcola quante sono le sottostringhe di s di lunghezza n con 2 vocali */
int subString(char *s, int n){
    int i,voc=0,sol=0;
    int len=strlen(s);
    int j; // Aggiunto


    // per ogni lettere cerca nelle n successive se sono presenti 2 vocali
    for(i=0;i<len-n;i++){ // aggiunto -n
        for(j=i;j<i+n;j++){
            if(toupper(s[j])=='A' || toupper(s[j])=='E' || toupper(s[j])=='I' ||
               toupper(s[j])=='O' || toupper(s[j])=='U'){
                voc++;
               }
        }
        // controllo e incremento della soluzione
        if(voc==2){
            sol++;
        }
        voc=0; // spostato da dentro l'if a fuori
    }
    return sol;
}
