//
// Created by Ruggero Nocera on 02/11/2019.
//

#include <stdio.h>
#include <ctype.h>
#define MAX 30

char *cercaRegexp(char *src, char *regexp);

int main(){
    char str[MAX];
    char rgx[MAX];
    printf("Inserisci stringa e regexp: ");
    scanf("%s %s", str, rgx);
    printf("Ho trovato: %s", cercaRegexp(str, rgx));
    return 0;
}

char *cercaRegexp(char *src, char *regexp){
    int i = 0, j = 0, k, t;
    int found = 0;
    int flag;
    while(src[i] != '\0' && !found){
        j = k = 0;
        found = 1;
        while(regexp[j] != '\0' && src[i+k] != '\0' && found){
            if(regexp[j] == '['){
                if(regexp[j+1] != '^') {
                    flag = 0;
                    for (t = j+1; regexp[t] != ']'; t++) {
                        if (src[i+k] == regexp[t]) flag = 1;
                    }
                    if (flag == 1) {
                        j = t;
                    } else {
                        found = 0;
                    }
                }else{
                    flag = 0;
                    for (t = j+2; regexp[t] != ']' && !flag; t++) {
                        if (src[i+k] == regexp[t]) flag = 1;
                    }
                    if (flag == 1) {
                        found = 0;
                    } else {
                        j = t;
                    }
                }
            }else if(regexp[j] == '\\'){
                if(regexp[j+1] == 'a'){
                    if(!islower(src[i+k])) found = 0;
                }else if(regexp[j+1] == 'A'){
                    if(!isupper(src[i+k])) found = 0;
                }
            }else if(regexp[j] != '.'){
                if(regexp[j] != src[i+k]) found = 0;
            }
            j++;
            k++;
        }
        i++;
        if(src[i] == '\0' && regexp[j] != '\0') found = 0;
    }
    if(!found) return NULL;
    return &src[--i];
}
