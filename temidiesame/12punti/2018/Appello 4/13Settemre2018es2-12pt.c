/*
Sia data una lista di interi, cui si accede mediante puntatore alla testa link1 head. Si scriva una
funzione C che costruisca una nuova lista “compressa”: per ogni elemento della prima lista si
memorizza nella seconda lista l’elemento stesso e il numero di ripetizioni consecutive nella prima. Si
definisca opportunamente il nodo della seconda lista. Il prototipo sia:
link2 comprimi(link1 head);
Esempio: se la prima lista è (3, 3, 3, 3, 2, 2, 3, 5, 5, 5), la seconda lista sarà ((3, 4), (2, 2), (3, 1), (5, 3))
*/
#include <stdio.h>
#include <stdlib.h>

typedef struct node* link;
struct node
{
	int val;
	link next;
};

typedef struct node2* link2;
struct node2
{
	int val1;
	int val2;
	link2 next;
};

link newnode1(int val, link next);
link2 newnode(int val1,int val2, link2 next);
link2 comprimi(link head);
link list();
void addlink2(link2 *head, link2 x);


int main()
{
	link x;
	link2 z;
	link head = list();
	link2 head2 = comprimi(head);
	for (z = head2; z != NULL; z = z->next)
	{
		printf("(%d %d) ", z->val1, z->val2);
	}
}

link list()
{
	link node5_2 = newnode1(5, NULL);
	link node5_1 = newnode1(5, node5_2);
	link node3_5 = newnode1(3, node5_1);
	link node2_2 = newnode1(2, node3_5);
	link node2_1 = newnode1(2, node2_2);
	link node3_4 = newnode1(3, node2_1);
	link node3_3 = newnode1(3, node3_4);
	link node3_2 = newnode1(3, node3_3);
	link node3_1 = newnode1(3, node3_2);
	return node3_1;
	/* lista: 3,3,3,3,2,2,3,5,5   */
}

link newnode1(int val, link next)
{
	link x;
	x = malloc(sizeof(*x));
	x->val = val;
	x->next = next;
	return x;
}

link2 newnode(int val1, int val2, link2 next)
{
	link2 x = malloc(sizeof(*x));
	x->val1 = val1;
	x->val2 = val2;
	x->next = next;
	return x;
}

link2 comprimi(link head)
{
	int count = 0;
	link p=head, x;
	link2 h;
	link2 head2=NULL;
	for (x = head; x != NULL; p = x, x = x->next)
	{
		if (x->val == p->val)
		{
			count++;
			if (x->next == NULL)
			{
				h = newnode(p->val, count, NULL);
				addlink2(&head2, h);
			}
		}
		else
		{
			h = newnode(p->val, count, NULL);
			addlink2(&head2, h);
			count = 1;
		}
	}
	return head2;
}

void addlink2(link2 *head, link2 x)
{
	link2 z, y;
	if (*head == NULL)
	{
		*head = x;
		return;
	}
	else
	{
		for (y = *head; y->next != NULL; y = y->next);
		y->next = x;

	}
	return;

}
