/*
albero di grado fissato N

funzione di visita ricorsiva, che visita l'albero e ritornare il conteggio del numero di nodi aventi grado (numero di figli) maggiore del grado del rispettivo nodo padre.

il nodo radice non ha un padre, conta 1 per default.
*/

/*
    tree.h
    typedef struct nTree_s *nTree;
    
    treeN.c
    typede struct node *link;
    struct node {
	char *key;
	struct node *children[N];
	int grado;
	};
     struct nTree_s {
  	link root;
     };	
     main.c
     //...
     int countIf(nTREE t);
     //..
     int main(){
         //...
         countIf(t);
         //...
     }
     
     ritorniamo a treeN.c
     int countIf(nTree t){
         int res=1;
         countIfR(t->root,&res,NULL);
         return res;
         
     }
     
    void countIfR(link actual,int *count,link dad) {
	    int i;
	    if(actual == NULL) return;
	    for(i=0;i<N;i++) if(actual->children[i]!= NULL) actual->grado++;
	    printf("%d %d\n",actual->data,actual->grado);
	    if(dad!=NULL) if(actual->grado > dad->grado) (*count)++;
	    for(i=0; i<N; i++) countIfR(actual->children[i],count,actual);
    } 


*/

//un main che permette di testare il codice in cui mancato ADT Ntree... ecc...
#include <stdio.h>
#include <stdlib.h>

#define N 3
struct Node {
    int data;
    struct Node* children[N]; // N è il grado fissato dell'albero
    int grado;
};

// funzione per creare un nuovo nodo
struct Node* newNode(int data) {
    struct Node* temp = (struct Node*)malloc(sizeof(struct Node));
    temp->data = data;
    temp->grado=0;
    for(int i=0; i<N; i++)
        temp->children[i] = NULL;
    return temp;
}


// funzione per visitare l'albero in modalità pre-order
void postOrder(struct Node* actual,int *count,struct Node *dad) {
    int i;
    if(actual == NULL) return; //se albero e vuoto o arrivo al figlio torno indietro 
    for(i=0;i<N;i++) if(actual->children[i]!= NULL) actual->grado++; //vedo qual è il grado per ciascun nodo scorrendo su tutti gli eventuali figli
    //printf("%d %d\n",actual->data,actual->grado);
    if(dad!=NULL) if(actual->grado > dad->grado) (*count)++; //se il padre non è nullo, ossia NON sono nella radice, posso verificare se il nodo corrente ha un grado maggiore del padre, se si incremento contatore
    for(i=0; i<N; i++) postOrder(actual->children[i],count,actual); //visita ricorsiva 
}





int main() {
    // creazione dell'albero
    struct Node* root = newNode(1);
    root->children[0] = newNode(2);
    root->children[1] = newNode(3);
    root->children[2] = newNode(4);
    root->children[0]->children[0] = newNode(5);
    root->children[0]->children[1] = newNode(6);
    root->children[2]->children[0] = newNode(7);

    // visita in pre-order
    int res=1;
    postOrder(root,res,NULL);
    printf("Res: %d\n",res);



    return 0;
}
