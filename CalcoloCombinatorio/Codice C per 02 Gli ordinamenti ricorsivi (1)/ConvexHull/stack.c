#include <stdlib.h>
#include "stack.h"

typedef struct STACKnode* link;
struct STACKnode
{
    void * node;
    link next;
};

static int N;
static  link head;

int STACKsize()
{
    return N;
}

link NEWnode(void * node)
{
    link x = malloc(sizeof *x);
    x->node = node;
    x->next = head;
    return x;
}

void STACKinit(int MaxN)
{
    head = NULL;
    N=0;
}

int STACKempty()
{
    return head == NULL;
}

void STACKpush(void * node)
{
    head = NEWnode(node);
    N++;
    return;
}

void * STACKpop()
{
    void * node = head->node;
    link t = head->next;
    free(head); head = t;
    N--;
    return node;
}

void * STACKtop()
{
    return head->node;
}

void * STACKnext_to_top()
{
    return head->next->node;
}
