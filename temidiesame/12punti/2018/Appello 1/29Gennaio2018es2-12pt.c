#include <stdio.h>
#include <stdlib.h>


typedef struct node *link;
struct node
{
    int val;
    link next;
};

//------------------------
link newnode();
int aggiungi(link);


int main()
{
  int n;
  link head=newnode();

  head->val=4;
  head->next=newnode();
  head->next->val=7;
  head->next->next=newnode();
  head->next->next->val=10;

  n=aggiungi(head);

  printf("\n\n%d nodi aggiunti\n",n);


    return 0;
}

link newnode()
{
    link x=malloc(sizeof(*x));
    x->next=NULL;
    x->val=-1;
    return x;
}

int aggiungi(link head)
{
    int i, j, n=0;
    link t=NULL, p=NULL;

    for(t=head; t!=NULL; t=t->next)
    {
        while(t->next != NULL && t->val != t->next->val-1 )
        {
            p=newnode();
            p->val = t->val+1;
            p->next = t->next;
            t->next = p;
            n++;
        }
    }

    for(t=head; t!= NULL ; t=t->next)
        printf("%d ",t->val);

    return n;

}
