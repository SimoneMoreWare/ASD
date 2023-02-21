#include <stdio.h>
#include <stdlib.h>

typedef struct node* link;
struct node
{
	int val;
	link left;
	link right;
};

void subtreewr(link root1, link root2,int *n,int *count);
link albero1();
link newnode(int val, link left, link right);
link albero2();
void subtreeR(link root1, link root2,int *n);
int subtree(link root1, link root2);
link albero3();

int main()
{
	link root1 = albero1();
	link root2 = albero2();
	link root3 = albero3();
	int n;
	n = subtree(root1, root2);
	if (n > 0)
	{
		printf("sottoalbero trovato\n");
	}
	else
	{
		printf("sottoalbero non trovato\n");
	}
}

link albero1()
{
	link nodo9 = newnode(9, NULL, NULL);
	link nodo2_1 = newnode(2, nodo9, NULL);
	link nodo2_2 = newnode(2, NULL, NULL);
	link nodo0 = newnode(0, NULL, NULL);
	link node1 = newnode(1, NULL, nodo0);
	link node7 = newnode(7, nodo2_2, nodo2_1);
	link node3 = newnode(3, node7, node1);
	return node3;
}

link albero2()
{
	link nodo9 = newnode(9, NULL, NULL);
	link nodo2_1 = newnode(2, nodo9, NULL);
	link nodo2_2 = newnode(2, NULL, NULL);
	link node7 = newnode(7, nodo2_2, nodo2_1);
	return node7;

}

link albero3()
{
	link node7 = newnode(7, NULL, NULL);
	link node1 = newnode(1, NULL,NULL);
	link node3 = newnode(3, node7, node1);
	return node3;
}

link newnode(int val, link left, link right)
{
	link x = malloc(sizeof(*x));
	x->left = left;
	x->right = right;
	x->val = val;
	return x;
}

void subtreewr(link root1, link root2,int *n,int *count)
{
	if (root1 == NULL)
	{
		return;
	}
	if (root1->val == root2->val)
	{
		*n = 1;
		subtreeR(root1, root2,n);
		if (*n == 1)
		{
			(*count)++;
		}
	}
	subtreewr(root1->left, root2,n,count);
	subtreewr(root1->right, root2,n,count);

}
void subtreeR(link root1, link root2, int* n)
{
	if (root2 == NULL)
		return;
	if (root1->val != root2->val)
		*n = 0;
	subtreeR(root1->left, root2->left, n);
	subtreeR(root1->right, root2->right, n);
}

int subtree(link root1, link root2)
{
	int n = 0;
	int count = 0;
	subtreewr(root1->left, root2, &n,&count);
	subtreewr(root1->right, root2, &n, &count);
	return count;
}
