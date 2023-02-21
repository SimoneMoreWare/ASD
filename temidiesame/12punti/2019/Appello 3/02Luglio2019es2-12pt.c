#include <stdio.h>
#include <stdlib.h>

typedef struct node* link;

struct node {
    char key;
    link next;
};
link createList();
link createNode(char key, link next);
link purgeList(link head1);
void printList(link head);

int main()
{
    link head1 = NULL, head2;

    head1 = createList();
    head2 = purgeList(head1);

    printList(head1);
    printList(head2);

    return 0;
}
link createNode(char key, link next){
    link x = malloc(sizeof(link));

    x->key = key;
    x->next = next;

    return x;
}

// a b ( a c g ) b e ( ) a ( x x ) f
link createList(){
    link nodo1,nodo2,nodo3,nodo4,nodo5,nodo6,nodo7,nodo8,nodo9,nodo10,nodo11,nodo12,nodo13,nodo14,nodo15,nodo16,nodo17;

    nodo17 = createNode('f', NULL);
    nodo16 = createNode(')',nodo17);
    nodo15 = createNode('x',nodo16);
    nodo14 = createNode('x',nodo15);
    nodo13 = createNode('(',nodo14);
    nodo12 = createNode('a',nodo13);
    nodo11 = createNode(')',nodo12);
    nodo10 = createNode('(',nodo11);
    nodo9 = createNode('e',nodo10);
    nodo8 = createNode('b',nodo9);
    nodo7 = createNode(')',nodo8);
    nodo6 = createNode('g',nodo7);
    nodo5 = createNode('c',nodo6);
    nodo4 = createNode('a',nodo5);
    nodo3 = createNode('(',nodo4);
    nodo2 = createNode('b',nodo3);
    nodo1 = createNode('a',nodo2);

    return nodo1;
}

void printList(link head){
    link x;

    for(x = head; x!=NULL; x=x->next)
        printf(" %c ", x->key);
    printf("\n");
}

// ab ( * ) b e ( * ) a ( * ) f
link purgeList(link head1){
    link x,p,t,head2 = NULL;

    for(x = head1; x!=NULL;x=x->next){
        p = createNode(x->key,NULL);

        if(x == head1){
            head2 = p;
        }else{
            t->next = p;
        }
        t = p;

        if(x->key == '('){
            p = createNode('*', NULL);
            t->next = p;
            while(x->next->key!=')')
                x = x->next;
            t->next = p;
            t = p;
        }
    }
    return head2;
}
