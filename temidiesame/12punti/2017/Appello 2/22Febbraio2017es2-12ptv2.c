#include <stdio.h>
#include <stdlib.h>

typedef struct node_t {
	char key;
	struct node_t* child;
	struct node_t* sibling;
	struct node_t* father;
	int numberOfChilds;
} node, *link;

link newborn(char key, link child, link sibling);
link tribu();
void censimento(link root);
void processTree(link root);

int main(int argc, char **argv)
{
	link albero = tribu();
	censimento(albero);
	processTree(albero);
	printf("\nProcessTree()...\n\n");
	censimento(albero);
}

link newborn(char key, link child, link sibling){
	// Questa è la funzione di creazione.
	// Non include numero di figli / padre perchè
	// Vanno aggiunti dopo con la funzione dell'esercizio
	link n = malloc(sizeof(node));
	n->key = key;
	n->child = child;
	n->sibling = sibling;
	n->father = NULL;
	n->numberOfChilds=-1; // So che sarebbe children ma ormai
	return n;
}

link tribu(){
	// L'albero in foto
	link b, h;
	h = newborn('j', NULL, NULL);
	h = newborn('i', NULL, h);
	h = newborn('h', NULL, h);
	h = newborn('e', h, NULL);
	b = newborn('g', NULL, NULL);
	b = newborn('f', NULL, b);
	b = newborn('d', b, NULL);
	b = newborn('c', NULL, b);
	b = newborn('b', h, b);
	return newborn('a', b, NULL);
}

void censimento(link root){
	if (root == NULL) return;
	printf("Nome: %c Numero di Figli: %c Padre: %c\n",
			root->key,
			root->numberOfChilds > -1 ? (char)( (int)'0' + root->numberOfChilds ) : '?',
			root->father == NULL ? '?' : root->father->key);
	censimento(root->child);
	censimento(root->sibling);
}

void processTreeR(link actual, link father){
	if (actual == NULL) return;
	if (actual->numberOfChilds == -1) actual->numberOfChilds = 0;
	actual->father = father;
	if (father != NULL) father->numberOfChilds++;
	processTreeR(actual->sibling, father);
	processTreeR(actual->child, actual);

}

void processTree(link root){
	processTreeR(root, NULL);
}