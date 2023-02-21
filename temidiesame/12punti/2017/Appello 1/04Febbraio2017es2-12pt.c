#include <stdio.h>
#include <stdlib.h>

typedef struct node_t {
	int key;
	struct node_t* left;
	struct node_t* right;
} node, *link;

link LINK(int key, link left, link right);
link albero();
link mirror(link root);
void visit(link root);

int main(int argc, char **argv)
{
	link l = albero();
	printf("Albero: ");
	visit(l);
	printf("\n");
	printf("Albero speculare: ");
	visit(mirror(l));
	printf("\n");
	return 420;
}

link LINK(int key, link left, link right){
	link l = malloc(sizeof(node));
	l->key = key;
	l->right = right;
	l->left = left;
	return l;
}

link albero(){
	// Lo stesso in foto all'esercizio
	link l = LINK(3, LINK(2, NULL, NULL), LINK(4, NULL, NULL));
	link r = LINK(18, LINK(17, NULL, NULL), LINK(20, NULL, NULL));
	l = LINK(6, l, LINK(7, NULL, NULL));
	return LINK(15, l, r);
}

void visit(link root){
	if (root == NULL) return;
	visit(root->left);
	printf("%d ", root->key);
	visit(root->right);
}

link mirror(link root){
	if (root == NULL) return NULL;
	return LINK(root->key, mirror(root->right), mirror(root->left));
}