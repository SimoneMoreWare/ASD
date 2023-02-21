/*
Scrivere la funzione:
int distance (nnode_t *root, int key1, int key2);
che, ricevuto un BST di radice root (di chiave intera) e due valori interi key1 e key2, restituisce il
numero di archi che è necessario attraversare per raggiungere il nodo di chiave key1 da quello di
chiave key2 (o viceversa).
Suggerimento: partendo dalla radice, la funzione distance proceda ricorsivamente lungo il BST
fintanto che il percorso per le chiavi key1 e key2 è comune e dia origine a due visite separate quando
il percorso di ricerca per le due chiavi si suddivide.
*/
#include <stdio.h>
#include <stdlib.h>

typedef struct node_t
{
	int key;
	struct node_t* left;
	struct node_t* right;
}nnode_t;
int distance(nnode_t* root, int key1, int key2);
nnode_t* newnode(int key, nnode_t* left, nnode_t* right);
nnode_t* albero();
int distanceR(nnode_t* root, int key2);

int main()
{
	nnode_t* mytree = albero();
	printf("Distanza tra 7 e 9: %d\n", distance(mytree, 7, 9));
	printf("Distanza tra 12 e 8: %d\n", distance(mytree, 12, 8));
	printf("Distanza tra 7 e 9: %d\n", distance(mytree, 7, 9));
	printf("Distanza tra 7 e 11: %d\n", distance(mytree, 7, 11));
	printf("Distanza tra 7 e 46: %d\n", distance(mytree, 7, 46));
	printf("Distanza tra 6 e 11: %d\n", distance(mytree, 6, 11));
}

nnode_t* albero()
{
	nnode_t* mytree = newnode(9, newnode(8, NULL, NULL), newnode(11, NULL, NULL));
	mytree = newnode(12, mytree, NULL);
	mytree = newnode(7, newnode(6, NULL, NULL), mytree);

	return mytree;
}

nnode_t* newnode(int key, nnode_t* left, nnode_t* right)
{
	nnode_t* x = malloc(1 * sizeof(*x));
	x->key = key;
	x->left = left;
	x->right = right;
	return x;
}

int distance(nnode_t* root, int key1, int key2)
{
	int k1left=0, k1right=0, k2left=0, key2right=0;
	int k;
	if (root == NULL)
		return 0;
	k = root->key;
	if (key1 == k)
	{
		key2right = distanceR(root->right, key2);
		k2left = distanceR(root->left, key2);
		if (key2right > 0)
		{
			key2right++;
			return key2right;
		}
		if (k2left > 0)
		{
			k2left++;
			return key2right;
		}
	}
	k1left = k1right = k2left = key2right = 0;
	if (key2 == k)
	{
		k1right = distanceR(root->right, key1);
		k1left = distanceR(root->left, key1);
		if (k1left > 0)
		{
			k1left++;
			return k1left;
		}
		if (k1right > 0)
		{
			k1right++;
			return k1right;
		}
	}
	k1left = k1right = k2left = key2right = 0;
	k1left = distanceR(root->left, key1)+1;
	k1right = distanceR(root->right, key1)+1;
	k2left = distanceR(root->left, key2)+1;
	key2right = distanceR(root->right, key2)+1;
	if (k1left >= 1 && k2left >= 1)
	{
		return(abs(k1left - k2left));
	}
	if (k1right >= 1 && key2right >=1)
	{
		return (abs(k1right - key2right));
	}
	if (k1left >=1 && key2right >= 1)
	{
		return k1left + key2right;
	}
	if (k1right >=1 && k2left >=1)
	{
		return k1right + k2left;
	}
}

int distanceR(nnode_t* root, int key2)
{
	int t = -1;
	if (root == NULL)
		return -1;
	if (root->key == key2)
		return 0;
	if (root->key > key2)
		t = distanceR(root->left, key2);
	else
		t = distanceR(root->right, key2);

	return t > -1 ? t + 1 : t;

}
