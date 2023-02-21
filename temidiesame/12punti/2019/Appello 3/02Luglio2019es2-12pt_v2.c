#include <stdio.h>
#include <stdlib.h>

typedef struct node *link;

struct node {
    char val;
    link next;
};

link createList();

link NEW(char val, link next);

link purgeList(link head1);

void printList(link head);

int main() {
    link head1 = NULL, head2;

    head1 = createList();
    head2 = purgeList(head1);

    printList(head1);
    printList(head2);

    return 0;
}

link NEW(char val, link next) {
    link x = malloc(sizeof(link));
    x->val = val;
    x->next = next;
    return x;
}

// a b ( a c g ) b e ( ) a ( x x ) f
link createList() {
    link nodo1, nodo2, nodo3, nodo4, nodo5, nodo6, nodo7, nodo8, nodo9, nodo10, nodo11, nodo12, nodo13, nodo14, nodo15, nodo16, nodo17;

    nodo17 = NEW('f', NULL);
    nodo16 = NEW(')', nodo17);
    nodo15 = NEW('x', nodo16);
    nodo14 = NEW('x', nodo15);
    nodo13 = NEW('(', nodo14);
    nodo12 = NEW('a', nodo13);
    nodo11 = NEW(')', nodo12);
    nodo10 = NEW('(', nodo11);
    nodo9 = NEW('e', nodo10);
    nodo8 = NEW('b', nodo9);
    nodo7 = NEW(')', nodo8);
    nodo6 = NEW('g', nodo7);
    nodo5 = NEW('c', nodo6);
    nodo4 = NEW('a', nodo5);
    nodo3 = NEW('(', nodo4);
    nodo2 = NEW('b', nodo3);
    nodo1 = NEW('a', nodo2);

    return nodo1;
}

void printList(link head) {
    link x;

    for (x = head; x != NULL; x = x->next)
        printf(" %c ", x->val);
    printf("\n");
}

link insTail(link h, char val) {
    link x;
    if (h == NULL)
        return NEW(val, NULL);
    for (x = h; x->next != NULL; x = x->next);
    x->next = NEW(val, NULL);
    return h;
}

// ab ( * ) b e ( * ) a ( * ) f
link purgeList(link head1) {
    link x, head2 = NULL;
    int ignore = 0;
    for (x = head1; x != NULL; x = x->next) {
        if (x->val == '(') {
            ignore = 1;
            head2 = insTail(head2, '(');
            head2 = insTail(head2, '*');
            head2 = insTail(head2, ')');
        } else if (x->val == ')')
            ignore = 0;
        else if (ignore == 0)
            head2 = insTail(head2, x->val);
    }
    return head2;
}