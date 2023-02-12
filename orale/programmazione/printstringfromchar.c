/*
 * data una stringa e un valore n, far slittare di n la stringa
 * (es: data la stringa programmazione e n=3 l’output dovrà essere oneprogrammazi)
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    char s[] = "programmazione";
    int len_s = (int) strlen(s);
    char *tmp = (char *) malloc((len_s) * sizeof(char));
    int i,j;
    int k=0;
    int n=3;
    for(i=0;i<2;i++){
        for(j=0;j<len_s;j++){
            tmp[k++]=s[j];
        }
    }
    tmp[k]='\0';
    printf("%s\n",tmp);
    for(i=len_s-n;i<(2*len_s-n);i++){
        printf("%c",tmp[i]);
    }
    free(tmp);
    return 0;
}
