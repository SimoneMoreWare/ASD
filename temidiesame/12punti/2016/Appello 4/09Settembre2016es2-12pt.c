#include <stdio.h>
#include <stdlib.h>

typedef struct node_t {
	int key;
	struct node_t* left;
	struct node_t* right;
} nnode_t;

int distance(nnode_t *root, int key1, int key2);
nnode_t* newnode(int key, nnode_t* left, nnode_t* right);
nnode_t* albero();

int main(int argc, char **argv){
	nnode_t* myTree = albero();
	printf("Distanza tra 12 e 11: %d\n", distance(myTree, 12, 11));
	printf("Distanza tra 12 e 8: %d\n", distance(myTree, 12, 8));
	printf("Distanza tra 7 e 9: %d\n", distance(myTree, 7, 9));
	printf("Distanza tra 7 e 11: %d\n", distance(myTree, 7, 11));
	printf("Distanza tra 7 e 46: %d\n", distance(myTree, 7, 46));
	
	return 420;
}

nnode_t* albero(){
	nnode_t* myTree = 
	newnode(9, newnode(8, NULL, NULL), newnode(11, NULL, NULL));
	myTree = newnode(12, myTree, NULL);
	myTree = newnode(7, newnode(6, NULL, NULL), myTree);

/*	
//					/( 7 )\
//				( 6 ) 	/( 12 )
//					/( 9 )\
//				( 8 ) 	( 11 )
//	
*/
	
	return myTree;
}

int max2(int a, int b){
	return a >= b ? a : b;
}

nnode_t* newnode(int key, nnode_t* left, nnode_t* right){
	nnode_t* nodo = malloc(sizeof(nnode_t));
	nodo->key = key;
	nodo->left = left;
	nodo->right = right;
	return nodo;
}

int distanceR(nnode_t* root, int key2) {
	int t = -1;
	if (root == NULL) return -1;
	if (root->key == key2) return 0;
	if (root->key > key2) t = distanceR(root->left, key2);
	else t = distanceR(root->right, key2);
	
	return t > -1 ? t + 1 : t;
}

int distance(nnode_t *root, int key1, int key2){
	int k;
	if (root == NULL) return -1;
	k = root->key;
	if (key1 == k) return distanceR(root, key2);
	
	return max2(distance(root->left, key1, key2), distance(root->right, key1, key2));
	
}

