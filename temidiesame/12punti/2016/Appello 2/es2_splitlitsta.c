/*
Il problema proposto consisteva nell'implementare una funzione C che dato una lista non ordinata di interi e un valore intero (soglia), 
dovesse dividere la lista in due: nella prima lista dovrebbero comparire gli elementi della lista originaria minori della soglia, 
nella seconda quelli maggiori o uguali alla soglia. Doveva essere mantenuto l'ordine relativo della lista originaria nelle due liste così create,
ma senza fare riferimento a funzioni di libreria sulle liste.

La funzione proposta, chiamata split_list, utilizza una singola passata sulla lista originaria, 
in cui si scorrono gli elementi uno per uno e si dividono in due liste separate in base al confronto con la soglia. 
Utilizza un ADT di I categoria per le liste con una struct wrapper di tipo lista_t.

La funzione split_list inizializza due nuove liste vuote (L1 e L2), quindi scorre gli elementi della lista originale L0 uno per uno. 
Per ogni elemento, se è minore della soglia, viene inserito in coda a L1; 
altrimenti, viene inserito in coda a L2. 

Una volta che tutti gli elementi sono stati elaborati, la funzione restituisce L1 e modifica L2 passato per riferimento.

La funzione utilizza una lista singola-collegata, e mantiene l'ordine relativo degli elementi presenti nella lista originaria. 
Utilizzando un puntatore alla testa della lista originaria, la funzione scorre gli elementi utilizzando un ciclo while e la condizione "current != NULL", 
questo permette di scorrere tutti gli elementi presenti nella lista originaria.

La funzione utilizza la funzione newNode per creare un nuovo nodo della lista, 
inizializzato con un valore dato e con un puntatore al nodo successivo. 
La funzione newNode utilizza la funzione malloc per allocare la memoria del nodo, 
in questo modo si evita di fare riferimento a funzioni delle librerie per la gestione delle liste.

In generale la funzione sviluppata sembra essere una soluzione corretta al problema proposto.
*/

typedef struct node *link;

struct node{
    int key;
    link next;
}

link split_list(int soglia,link L0,link *L2){
    link tmp0=L0; //punto alla testa del vettore originale
    link L1=NULL;
    while(tmp0!=NULL){
        if(tmp0->key < soglia){
            //lista 1
            L1=listInsTail(L1,tmp0->key);
        }else{
            //lista 2
            (*L2)=listInsTail((*L2),tmp0->key));
        }
        tmp0=tmp0->next;
    }
    return L1;
}

link listInsTail(link h, int val) {
	link x;
	if (h==NULL) return newNode(val, NULL);
	for (x=h; x->next!=NULL; x=x->next);
        x->next = newNode(val, NULL);
        return h;
}

link newNode(link next,int val){
    link x=malloc(sizeof(*x));
    if(x==NULL) exit(-1);
    else{
        x->next=next;
        x->val=val;
    }
    return x;
}
