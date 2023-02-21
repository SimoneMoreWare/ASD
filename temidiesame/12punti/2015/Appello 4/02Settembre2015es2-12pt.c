#include <stdio.h>
#include <stdlib.h>

//typedef int Key;

typedef struct node_t {
	int key;
	struct node_t* left;
	struct node_t* right;
} node;

node* nodo(int key, node* left, node* right){
	node* r = malloc(sizeof(node));
	r->key = key;
	r->left = left;
	r->right = right;
	return r;
}

node* treeUno(){
	node* t0, *t1, *t2; //Albero semplice
	t2 = nodo(2, NULL, NULL);
	t1 = nodo(1, NULL, NULL);
	t0 = nodo(0, t1, t2);
	
	return t0;
}

node* treeDue(){
	node* t0, *t1, *t2; //Albero semplice
	t2 = nodo(2, NULL, NULL);
	t1 = nodo(1, NULL, NULL);
	t0 = nodo(5, t1, t2);
	return t0;
}

int TREEisomorph(node* t1, node* t2){
	if (t2 == NULL){
		if (t1 == NULL) return 1;
		else return 0;
	}
	if (t1 == NULL) return 0;
	
	if(t1->key == t2->key)
		return TREEisomorph(t1->left, t2->left)
			&& TREEisomorph(t1->right, t2->right);
	return 0;
}

int main(int argc, char **argv)
{
	printf("%d %d %d",
	TREEisomorph(treeUno(), treeUno()),
	TREEisomorph(treeUno(), treeDue()),
	TREEisomorph(treeUno(), NULL));
	printf("\n");
}
