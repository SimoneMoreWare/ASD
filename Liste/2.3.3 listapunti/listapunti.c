#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>


typedef struct {
  float x, y, dist;
} Punto;

typedef float Dist;

typedef struct node *link;

struct node {
  Punto point;
  link next;
};

typedef struct {
  link head;
} list;

Dist getDist(Punto point)  {
  return point.dist;
}

int distGreater(Dist d1, Dist d2)  {
  return (d1>d2);
}

float distFromOrig(Punto point) {
	return sqrt(point.x*point.x + point.y*point.y);
}

Punto Puntoscan() {
  float x, y;
  Punto point;
  printf("x= ");
  scanf("%f", &x);
  printf("y= ");
  scanf("%f", &y);
  point.x = x;
  point.y = y;
  point.dist = distFromOrig(point);
  return point;
}

void Puntodisplay(Punto point) {
  printf("<%f, %f> [%f]\n", point.x, point.y, point.dist);
}

list *listInit() {
  list *l = malloc(sizeof(list));
  if (l == NULL)
    return NULL;
  l->head = NULL;
  return l;
}

link newNode(Punto point, link next) {
  link x = malloc(sizeof *x);
  if (x == NULL)
    return NULL;
  x->point = point;
  x->next = next;
  return x;
}

void listDisplay(list *l) {
  link tmp;
  if (l == NULL)
    return;
  tmp = l->head;
  while(tmp != NULL) {
    Puntodisplay(tmp->point);
    tmp = tmp->next;
  }
}

void SortListIns(list *l, Punto point) {
  link x, p;
  Dist k = getDist(point);
  if (l->head==NULL || distGreater(getDist(l->head->point),k)) {
    l->head = newNode(point, l->head);
  }
  else {
    for (x=l->head->next, p=l->head; x!=NULL && distGreater(k,getDist(x->point)); p=x, x=x->next);
    p->next = newNode(point, x);
  }
}

void freeList(list *l) {
    link t, p;

    if (l== NULL)
        return;

    p = l->head;
    while (p != NULL) {
        t = p;
        p = p->next;
        free(t);
    }
    free(l);
}

int main(void) {
  int i, n=4;
  list *l = listInit();
  Punto point;
  for (i=0; i<n; i++) {
    printf("Inserire coordinate del prossimo punto:\n");
	point = Puntoscan();
    SortListIns(l, point);
  }
  printf("La lista ordinata per distanze dall'origine crescenti e': \n");
  listDisplay(l);
  freeList(l);
  return 0;
}
