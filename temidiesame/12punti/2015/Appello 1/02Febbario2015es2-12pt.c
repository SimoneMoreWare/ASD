#include <stdio.h>
#include <stdlib.h>

#define N 2

typedef struct node {
	int chiave;
	struct node* figli[N];
} node;

typedef struct node* LINK;

void visitLevelByLevel(struct node* root, int l1, int l2);
node* albero();
node* albero2();

int main(int argc, char **argv)
{
	printf("Inizio esecuzione.\n");
	printf("Genero albero...");
	LINK root = albero();
	printf("\nAlbero generato.");
	printf("Visito l'albero da profondita' 1 (2) a 2 (3)...\n");
	visitLevelByLevel(root, 1, 2);
	printf("\nVisito l'albero da profondita' 0 (1) a 3 (4)...\n");
	visitLevelByLevel(root, 0, 3);
	printf("\nVisito l'albero da profondita' 2 (3) a 2 (3)...\n");
	visitLevelByLevel(root, 2, 2);
	
	printf("\n\n\nCambio albero...\n");
	root = albero2();
	printf("Albero cambiato.\n\n\n");
	
	printf("Visito l'albero da profondita' 1 (2) a 2 (3)...\n");
	visitLevelByLevel(root, 1, 2);
	printf("\nVisito l'albero da profondita' 0 (1) a 3 (4)...\n");
	visitLevelByLevel(root, 0, 3);
	printf("\nVisito l'albero da profondita' 2 (3) a 2 (3)...\n");
	visitLevelByLevel(root, 2, 2);
	
	return 420;
}

// La soluzione sono ste 4 righe, tutto il resto e' testing...
void print_profondita(node* root, int profondita_necessaria, int profondita_attuale){
	if (root == NULL) return;
	if (profondita_necessaria == profondita_attuale){
		printf("%d ", root->chiave);
		return;
	}
	for(int i=0; i<N; i++) print_profondita(root->figli[i], profondita_necessaria, profondita_attuale+1);
}

void visitLevelByLevel(struct node* root, int l1, int l2){
	for(int i=l1; i <= l2; i++) print_profondita(root, i, 0);
}

node* create(int chiave, node* figli[N]){
	node* nodo = malloc(sizeof(node));
	nodo->chiave = chiave;
	for(int i=0; i<N; i++) nodo->figli[i] = figli[i];
	return nodo;
}


node* albero(){
	LINK f1, f11, f12, f111, f112, f121, f122, f1111, f1112, f1121, f1122, f1211, f1212, f1221, f1222;
	
	f1111 = create(1111, (node* [2]){NULL, NULL});
	f1112 = create(1112, (node* [2]){NULL, NULL});
	f1121 = create(1121, (node* [2]){NULL, NULL});
	f1122 = create(1122, (node* [2]){NULL, NULL});
	f1211 = create(1211, (node* [2]){NULL, NULL});
	f1212 = create(1212, (node* [2]){NULL, NULL});
	f1221 = create(1221, (node* [2]){NULL, NULL});
	f1222 = create(1222, (node* [2]){NULL, NULL});
	
	f111 = create(111, (node* [2]){f1111, f1112});
	f112 = create(112, (node* [2]){f1121, f1122});
	f121 = create(121, (node* [2]){f1211, f1212});
	f122 = create(122, (node* [2]){f1221, f1222});
	
	f11 = create(11, (node* [2]){f111, f112});
	f12 = create(12, (node* [2]){f121, f122});
	
	f1 = create(1, (node* [2]){f11, f12});
	
	// Voglio morire
	
	return f1;
}

node* albero2(){
	LINK f1, f11, f12, /*f111,*/ f112, f121, /*f122, f1111, f1112, f1121,*/ f1122, f1211, f1212 /*f1221, f1222*/;
	
	/*f1111 = create(1111, (node* [2]){NULL, NULL});
	f1112 = create(1112, (node* [2]){NULL, NULL});
	f1121 = create(1121, (node* [2]){NULL, NULL});*/
	f1122 = create(1122, (node* [2]){NULL, NULL});
	f1211 = create(1211, (node* [2]){NULL, NULL});
	f1212 = create(1212, (node* [2]){NULL, NULL});
	/*f1221 = create(1221, (node* [2]){NULL, NULL});*/
	/*f1222 = create(1222, (node* [2]){NULL, NULL});*/
	
	/*f111 = create(111, (node* [2]){f1111, f1112});*/
	f112 = create(112, (node* [2]){NULL, f1122}); // !
	f121 = create(121, (node* [2]){f1211, f1212});
	/*f122 = create(122, (node* [2]){f1221, f1222});*/
	
	f11 = create(11, (node* [2]){NULL, f112}); // !
	f12 = create(12, (node* [2]){f121, NULL}); // !
	
	f1 = create(1, (node* [2]){f11, f12});
	
	// Voglio morire
	
	return f1;
}