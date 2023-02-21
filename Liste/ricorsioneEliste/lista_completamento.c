#include <stdio.h>
#include <stdlib.h>

typedef struct node_ {
   struct node_ *next;
   int val;
 } node;

typedef node *link;

typedef struct list_ {
  link head;
} list;

link newNode(int val, link next) {
  link n = calloc(1, sizeof(node));
  if (n == NULL) return NULL;
  n->val = val;
  n->next = next;
  return n;
}

int aggiungi(list *l) {
  link start, end, iter;
  int i, count = 0;
  if (l == NULL || l->head == NULL)
    return -1;
  for(start = l->head, end = l->head->next;
      start != NULL && end != NULL;
      start = end, end = end->next) {
    i = start->val;
    iter = start;
    while(++i < end->val) {
      count++;
      iter->next = newNode(i, end);
      iter = iter->next;
    }
  }
  return count;
}
void freeList(list *l) {
  link t, p;
  if (l== NULL) return;
  p = l->head;
  while (p != NULL) {
    t = p;
    p = p->next;
    free(t);
  }
  free(l);
}

void printList(FILE *fp, list *l) {
  link p;
  if (l == NULL) return;
  p = l->head;
  while (p != NULL) {
    fprintf(fp, "%d ", p->val);
    p = p->next;
  }
  fprintf(fp, "\n");
}

int main() {
  /* Setup lista iniziale */
  int res;
  list *l = calloc(1, sizeof(list));
  if (l == NULL) exit (-1);
  l->head = newNode(4, newNode(7, newNode(10, NULL)));
  if (l->head == NULL) exit (-1);
  printList(stdout, l);
  res = aggiungi(l);
  if (res == -1) exit (-1);
  printList(stdout, l);
  freeList(l);
  return 0;
}
