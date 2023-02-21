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
    int val;
    int ripetizioni;
    link2 next;
};

link newnode1(int val, link next);
link2 comprimi(link head);
link list();
link2 inserisciincoda2(link2 head2,int val,int count_consecutivi);

int main()
{
    link2 z;
    link head = list();
    link2 head2 = comprimi(head);
    for (z = head2; z != NULL; z = z->next)
    {
        printf("(%d %d) ", z->val, z->ripetizioni);
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



link2 comprimi(link head)
{
    link2 head2 = NULL;
    int count_consecutivi=0;
    link tmp = head;
    link pred = tmp;
    while(tmp!=NULL){
        if(tmp->val == pred->val){
            count_consecutivi++;
            if(tmp->next==NULL) head2=inserisciincoda2(head2,pred->val,count_consecutivi+1);
        }else{
            head2=inserisciincoda2(head2,pred->val,count_consecutivi);
            count_consecutivi=1;
        }
        pred=tmp;
        tmp=tmp->next;
    }

    return head2;
}

link2 inserisciincoda2(link2 head2,int val,int count_consecutivi){
    link2 x = malloc(sizeof *x);

    if(x==NULL) return NULL;

    if(head2==NULL){
        x->val=val;
        x->ripetizioni=count_consecutivi;
        x->next=NULL;
        return x;
    }

    link2 tmp = head2;
    while(tmp->next!=NULL) tmp=tmp->next;

    //qui mi ritrovo nell'ultimo nodo
    x->val=val;
    x->ripetizioni = count_consecutivi;
    x->next=NULL;
    tmp->next=x;
    return head2;

}
