#include <stdio.h>
#include <stdlib.h>

typedef struct node *link;

struct node
{
  int item;
  link next;
};

int count (link x);
void traverse (link h);
void traverseR (link h);
link delet(link x, int item);

int main(int argc, char *argv[]) {

  int i, N;
  link x, t;

  if (argc < 2) {
    printf("Error: missing argument\n");
    printf("Correct format:\n");
    printf("%s N \n", argv[0]);
    return 0;
  }

  N = atoi(argv[1]);

  t = malloc(sizeof *t);

  x = t;
  t->item =1;
  t->next =NULL;

  printf("The i-th element in the list is: %d\n", t->item);

  for (i = 2; i <=N; i++) {
    x = (x->next = malloc(sizeof *x));
    x->item = i; x->next = NULL;
    printf("The i-th element in the list is: %d\n", x->item);
  }

  printf("Count the number of elements in the  list\n");
  printf("The list has %d elements \n", count(t));

  printf("Visit the list \n");
  traverse(t);
  printf("\n");

  printf("Visit the list in reverse order \n");
  traverseR(t);
  printf("\n");

  printf("Input element to be removed:");
  scanf("%d", &i);
  printf("List after deleting element %d\n", i);
  traverse ( t = delet(t, i));
  printf("\n");

  return 0;
}

int count (link x) {
  if (x == NULL)
    return 0;
  return 1 + count(x->next);
}

void traverse (link h) {
  if (h == NULL)
    return;
  printf("%d ", h->item);
  traverse(h->next);
}

void traverseR (link h) {
  if (h == NULL)
    return;
  traverseR(h->next);
  printf("%d ", h->item);
}

link delet(link x, int v) {
  link t;
  if ( x == NULL )
    return NULL;
  if ( x->item == v) {
    t = x->next;
    free(x);
    return t;
  }
  x->next = delet(x->next, v);
  return x;
}
