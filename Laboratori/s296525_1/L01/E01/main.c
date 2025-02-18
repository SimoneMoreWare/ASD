#include <stdio.h>
#include <string.h>
#include <stdbool.h>

char* cercaRegexp(char *src, char *regexp){
    int i = 0, len_src = strlen(src), len_regexp = strlen(regexp);
    while(i < len_src) {
        int j = 0, k = 0;
        while((j+k) < len_regexp) {
            bool exit_cicle = false;
            // se la posizione in regexp è un punto
            if (regexp[j+k] == '.') {
                ;
            } 
            // se la posizione in regexp è una parentesi
            else if (regexp[j+k] == '[') {
                k = k + 1;
                // se non vuole i caratteri interni
                if (regexp[j+k] == '^') {
                    k = k + 1;
                    do {
                        if (regexp[j+k] == src[i+j]) {
                            while (regexp[j+k] != ']'){
                                k = k + 1; 
                            }
                            exit_cicle = true;
                            break;
                        }
                        k = k + 1;
                    } while(regexp[j+k] != ']');
                } 
                // se vuole i caratteri interni
                else {
                    bool found = false;
                    do {
                        if (regexp[j+k] == src[i+j]) {
                            found = true;
                            while (regexp[j+k] != ']'){
                                k = k + 1; 
                            }
                            break;
                        }
                        k = k + 1;
                    } while(!found && regexp[j+k] != ']');
                    if (!found) {
                        exit_cicle = true;
                    }
                }
            }
            // se la posizione in regexp è uno slash
            else if (regexp[j+k] == '\\') {
                k = k + 1;
                if ((regexp[j+k] == 'a' && !(src[i+j] >= 'a' && src[i+j] <= 'z')) ||
                    (regexp[j+k] == 'A' && !(src[i+j] >= 'A' && src[i+j] <= 'Z'))) {
                    exit_cicle = true;
                }
            }
            // posizione in regexp è per forza una lettera
            else if (regexp[j+k] != src[i+j]) {
                exit_cicle = true;
            }
            /* se un carattere non ha rispettato una condizione della regexp, 
               passa alla prossima sottostringa
            */
            if (exit_cicle) {
                break;
            }
            j = j + 1;
        }
        if ((j+k) == len_regexp) {
            return src + i;
        }
        i = i + 1;
    }
    return NULL;
}

int main(void){
    char *src = "asSoSasSo", *regexp = ".[sS]a\\a\\A[^efg]";
    printf("%s \n", regexp);
    char *found = cercaRegexp(src, regexp);
    if (found != NULL) {
        printf("E' stata trovata una corrispondenza.");
    } else {
        printf("Non e' stata trovata una corrispondenza.");
    }
}