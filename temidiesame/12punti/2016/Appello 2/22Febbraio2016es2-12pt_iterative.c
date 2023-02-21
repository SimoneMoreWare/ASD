#include <stdio.h>
#include <stdlib.h>

typedef struct node_t {
	int key;
	struct node_t* next;
} *node;

typedef struct list_t {
	node head;
} list;


#define L0SZ 19
#define MAXVAL 23


node NODEcreate(int key, node next);
void LISTprint(list* l);
void LISTinsert(list* l, int key);

list* split_list(int soglia, list* L0, list** L2);

int main(int argc, char **argv){
	list *L0, *L1, *L2;
	L0 = malloc(sizeof(list));
	L0->head = NULL;
	int i, soglia;
	printf("Popolo lista\n");
	for(i=0; i<L0SZ; i++) LISTinsert(L0, rand() % MAXVAL + 1);
	
	printf("L0: "); LISTprint(L0); printf("\n");
	soglia = L0SZ/2;
	printf("Soglia scelta: %d\n", soglia);
	
	L1 = split_list(soglia, L0, &L2);
	printf("L1: "); LISTprint(L1); printf("\n");
	printf("L2: "); LISTprint(L2); printf("\n");
	
	return 420;
}

list* split_list(int soglia, list* L0, list** L2){
	list *L1 = malloc(sizeof(list));
	*L2 = malloc(sizeof(list));
	L1->head = NULL;
	(*L2)->head = NULL;
	
	list L3; L3.head = NULL;
	node n;
	
	for(n = L0->head; n != NULL; n = n->next){
		L3.head = NODEcreate(n->key, L3.head);
	}
	
	for(n = L3.head; n != NULL; n = n->next){
		if (n->key >= soglia) L1->head = NODEcreate(n->key, L1->head);
		else (*L2)->head = NODEcreate(n->key, (*L2)->head);
	}
	
	return L1;

}
	
void LISTinsert(list* l, int key){
	l->head = NODEcreate(key, l->head);
}

node NODEcreate(int key, node next){
	node n = malloc(sizeof(struct node_t));
	n->key = key;
	n->next = next;
	return n;
}

void LISTprint(list* l){
	node n;
	for(n=l->head; n != NULL; n=n->next) printf("%d ", n->key);
	return;
}
