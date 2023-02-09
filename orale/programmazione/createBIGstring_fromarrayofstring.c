#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char **argv) {
    // Vettore di puntatori a stringhe
    char *strings[] = { "Hello", "world", "!" };
    int num_strings = sizeof(strings) / sizeof(char *);

    // Calcola la lunghezza totale della stringa
    int total_len = 0;
    for (int i = 0; i < num_strings; i++) {
        total_len += strlen(strings[i]);
    }

    // Alloca la stringa più grande
    char *big_string = (char *) malloc(total_len + 1);
    if (!big_string) {
        printf("Errore nell'allocazione della memoria\n");
        return 1;
    }

    // Copia le sottostringhe nella stringa più grande
    int offset = 0;
    for (int i = 0; i < num_strings; i++) {
        int len = strlen(strings[i]);
        memcpy(big_string + offset, strings[i], len);
        offset += len;
    }
    big_string[total_len] = '\0';

    // Stampa la stringa più grande
    printf("Stringa piu grande: %s\n", big_string);

    // Dealloca la stringa più grande
    free(big_string);

    return 0;
}
