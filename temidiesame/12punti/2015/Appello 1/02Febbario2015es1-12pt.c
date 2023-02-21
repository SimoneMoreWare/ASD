#include <stdio.h>
#include <stdio.h>
#include <string.h>

#define STRLEN 64+1

/*
 * Probabilmente questa soluzione
 * è un po' piu complicata e non
 * è esattamente quello che vorrebbero
 * C&C, ma vabbè;
 */

void eraseDuplicate(char* str);

int main(int argc, char **argv)
{
	char str[STRLEN] = "aa;;;bbbab;\0";
	printf("Inizio esecuzione");
	printf("\nStringa originale: %s\n", str);
	printf("Rimuovo duplicati...\n");
	eraseDuplicate(str);
	printf("Caratteri unici: %s\n", str);
	printf("Termino esecuzione.\n");
	return 420;
}

void eraseDuplicate(char* str){
	char occorrenze[STRLEN] = "", *str_p = str, char_t[2];
	int pos = 0;
	while( (*str_p) != '\0'){
		char_t[0] = (*str_p);
		char_t[1] = '\0';
		if ( strstr(occorrenze, char_t) == NULL){
			occorrenze[pos++] = char_t[0];
			occorrenze[pos] = '\0';
		}
		str_p++;
	}
	occorrenze[++pos] = '\0';
	strcpy(str, occorrenze);
}