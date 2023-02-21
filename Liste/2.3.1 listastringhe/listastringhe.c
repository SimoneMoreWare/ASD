#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct nodo_ nodo, *link;

struct nodo_ {
    char *str;
    link next;
};

typedef struct lista_ {
    link head;
    int num;
} lista;

link NEW(char *s, link l) {
    link p = (link)malloc(sizeof(nodo));
    if (p == NULL) {
        printf("Errore di allocazione di memoria\n");
        return NULL;
    }

    p->str = strdup(s);
    p->next = l;
    return p;
}

lista *crea_lista() {
    lista *qp;

    qp = (lista *)malloc(sizeof(lista));
    if (qp == NULL) {
        printf("Errore di allocazione di memoria\n");
        return NULL;
    }
    qp->head = NULL;
    qp->num = 0;
    return qp;
}

void libera_lista(lista *qp) {
    link t, p;

    if (qp == NULL)
        return;

    p = qp->head;
    while (p != NULL) {
        t = p;
        p = p->next;
        free(t->str);
        free(t);
    }
    free(qp);
}

int inserisci_lista(lista *qp, char *str) {
  link t, p, x;
  if (qp == NULL)
    return 1;

  t = NEW(str,NULL);
  if (t == NULL)
    return 1;

  if (qp->head == NULL) {
    qp->head = t;
  } else {
    x = qp->head;
    p = NULL;
    while(x != NULL && strcmp(x->str, str) < 0) {
      p = x;
      x = x->next;
    }
    if (p == NULL) {
      t->next = qp->head;
      qp->head = t;
    } else {
      t->next = x;
      p->next = t;
    }
  }
  qp->num++;
  return 0;
}

void stampa_lista(FILE *fp, lista *qp) {
    link p;

    if (qp == NULL)
        return;

    p = qp->head;
    while (p != NULL) {
        fprintf(fp, "%s\n", p->str);
        p = p->next;
    }
}

lista *carica_lista(FILE *fp) {
    char str[31];
    lista *qp;

    qp = crea_lista();
    if (qp == NULL)
        return NULL;

    while (fscanf(fp, "%s", str) == 1) {
        inserisci_lista(qp, str);
    }
    return qp;
}

int main(int argc, char **argv) {
    FILE *in;
    lista *l;

    in = fopen(argv[1], "r");
    if (in == NULL)
       return -1;
    l = carica_lista(in);
    fclose(in);
    stampa_lista(stdout, l);
    libera_lista(l);
    return 0;
}
