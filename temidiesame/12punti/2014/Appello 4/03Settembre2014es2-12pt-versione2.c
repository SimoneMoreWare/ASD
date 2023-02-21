#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define STRLEN 50+1

typedef struct node_t {
	char* stringa;
	struct node_t* prossimo;
} node_t;

node_t* splitStr(char* str);

int main(int argc, char **argv)
{
	char stringa[STRLEN] = "a.bb.ccc.dddd.eeeee.ffffff\0";
	node_t* lista;
	printf("Inizio esecuzione.\n");
	printf("Stringa da spezzare: %s\n", stringa);
	printf("Spezzo la stringa...\n");
	lista = splitStr(stringa);
	printf("Stringa spezzata. Attraversamento: \n");
	for(; lista->prossimo != NULL; lista = lista->prossimo)
		printf("%s ", lista->stringa);
	printf("\nTermino esecuzione.\n");
	
	return 420;
	
}

node_t* nodo(char* stringa, node_t* prossimo){
	node_t* node = malloc(sizeof(node_t));
	node->stringa = malloc(STRLEN*sizeof(char));
	strcpy(node->stringa, stringa);
	node->prossimo = prossimo;
	return node;
}

node_t* splitStr(char* str){
	char tempStringa[STRLEN];
	int pos = 0;
	node_t* lista = nodo("", NULL);
	while( (*str) != '\0'){
		if ( (*str) != '.'){
			tempStringa[pos] = (*str);
			pos++;
		}
		else {
			lista = nodo(tempStringa, lista);
			pos = 0;
		}
		str++;
	}
	
	return lista;
}