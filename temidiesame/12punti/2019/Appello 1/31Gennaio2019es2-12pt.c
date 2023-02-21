#include <stdio.h>
#include <stdlib.h>

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

typedef struct l1 * link1;
struct l1 {
	int val;
	link1 ptr;
};

typedef struct l2 * link2;
struct l2 {
	int val;
	int num;
	link2 ptr;
};

link2 comprimi(link1 head);
void stampa1(link1 head);
void stampa2(link2 head);

int main(void) 
{
    struct l1 list1[10];
	link1 head1;
	link2 head2;
	
	list1[0].val = 3;
	list1[0].ptr = &list1[1];
	list1[1].val = 3;
	list1[1].ptr = &list1[2];
	list1[2].val = 3;
	list1[2].ptr = &list1[3];
	list1[3].val = 3;
	list1[3].ptr = &list1[4];
	list1[4].val = 2;
	list1[4].ptr = &list1[5];
	list1[5].val = 2;
	list1[5].ptr = &list1[6];
	list1[6].val = 3;
	list1[6].ptr = &list1[7];
	list1[7].val = 5;
	list1[7].ptr = &list1[8];
	list1[8].val = 5;
	list1[8].ptr = &list1[9];
	list1[9].val = 5;
	list1[9].ptr = NULL;
	
	head1 = &list1[0];
	stampa1(head1);
	head2 = comprimi(head1);
	stampa2(head2);
	
	return 0;
}

link2 comprimi(link1 head)
{
	link2 head2, ptr2, tmp2;
	link1 ptr1;
	int num, val;
	
	ptr1 = head;
	head2 = NULL;
	num = 0;
	while (ptr1 != NULL) { 
		if (num == 0) {
			tmp2 = (link2)malloc(sizeof(struct l2));
			tmp2->val = ptr1->val;
			tmp2->num = 0;
			tmp2->ptr = NULL;
			if (head2 == NULL) {
				head2 = tmp2;
				ptr2 = tmp2;
			} else {
				ptr2->ptr = tmp2;
				ptr2 = tmp2;
			}
		}
		if (ptr1->val == ptr2->val) {
			num++;
			ptr2->num++;
			ptr1 = ptr1->ptr;
		} else {
			num = 0;
		}
	} 
	return head2;
}

void stampa1(link1 head)
{
	link1 ptr = head;
	printf("LISTA 1\n");
	while (ptr != NULL) {
		printf("Val = %d\n", ptr->val);
		ptr = ptr->ptr;
	}
	printf("\n");
}

void stampa2(link2 head)
{
	link2 ptr = head;
	printf("LISTA 2\n");
	while (ptr != NULL) {
		printf("Val = %d, num = %d\n", ptr->val, ptr->num);
		ptr = ptr->ptr;
	}
	printf("\n");
}
