/*
La funzione utilizza due puntatori, slow e fast, che scorrono la lista. Il puntatore slow avanza di un nodo alla volta,
mentre il puntatore fast avanza di due nodi alla volta. Se i due puntatori si incontrano, significa che c'è un ciclo nella lista. 
A questo punto, la funzione riposiziona il puntatore slow all'inizio della lista e li fa scorrere entrambi di un nodo alla volta finché non 
si incontrano di nuovo. Il nodo in cui si incontrano è il punto di ripiegamento della lista.

Se la lista non ha un ciclo, i due puntatori si fermeranno alla fine della lista e la funzione restituirà NULL.
*/

#include <stdio.h>
#include <stdlib.h>

struct node {
    int data;
    struct node *next;
};

struct node *detect_loop(struct node *head) {
    struct node *slow = head, *fast = head;

    while (fast != NULL && fast->next != NULL) {
        slow = slow->next;
        fast = fast->next->next;

        if (slow == fast) {
            slow = head;
            while (slow != fast) {
                slow = slow->next;
                fast = fast->next;
            }
            return slow;
        }
    }
    return NULL;
}

int main(void) {
    struct node *head = NULL;
    struct node *n1 = (struct node *)malloc(sizeof(struct node));
    struct node *n2 = (struct node *)malloc(sizeof(struct node));
    struct node *n3 = (struct node *)malloc(sizeof(struct node));
    struct node *n4 = (struct node *)malloc(sizeof(struct node));
    struct node *n5 = (struct node *)malloc(sizeof(struct node));

    n1->data = 1;
    n2->data = 2;
    n3->data = 3;
    n4->data = 4;
    n5->data = 5;

    head = n1;
    n1->next = n2;
    n2->next = n3;
    n3->next = n4;
    n4->next = n5;
    n5->next = n3;

    struct node *node = detect_loop(head);
    if (node != NULL) {
        printf("La lista si ripiega su se stessa alla terminazione in nodo con dato %d\n", node->data);
    } else {
        printf("La lista non si ripiega su se stessa\n");
    }

    return 0;
}
