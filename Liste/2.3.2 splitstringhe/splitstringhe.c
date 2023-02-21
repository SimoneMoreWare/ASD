#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct node *link, nodo;

struct node {
  char *str;
  link next;
};


link newNode(char *str, link next) {
  link x = malloc(sizeof *x);
  if (x == NULL)
    return NULL;
  x->str = strdup(str);
  x->next = next;
  return x;
}

void listInsTailFast(link *hp, link *tp, char *str) {
  if ((*hp) == NULL)
    *hp = *tp = newNode(str, NULL);
  else {
	(*tp)->next = newNode(str, NULL);
	(*tp) = (*tp)->next;
  }
}


nodo *splitStringa(char *str, char sep) {
  int len = strlen(str), i, sublen;
  char *substr;
  link head, tail;
  head = tail = NULL;
  for (i=0; i<len; i++)
    if (str[i] == sep)
      str[i] = '\0';
  for(i=0;i<len;i++) {
    sublen = strlen(str+i);
    substr = strdup(str+i);
    listInsTailFast(&head, &tail, substr);
    i += sublen;
    free(substr);
  }
  return head;
}

void listDisplay(link h) {
  link tmp;
  if (h == NULL)
    return;
  tmp = h;
  while(tmp != NULL) {
    printf("%s\n", tmp->str);
    tmp = tmp->next;
  }
}

void libera_lista(link head) {
    link t, p;

    if (head == NULL)
        return;

    p = head;
    while (p != NULL) {
        t = p;
        p = p->next;
        free(t->str);
        free(t);
    }
}

int main(void) {
	char *str = strdup("aaaa.bbb.cc.d");
	char sep = '.';
	link l;
	l = splitStringa(str, sep);
	listDisplay(l);
        libera_lista(l);
        free(str);
	return 0;
}

