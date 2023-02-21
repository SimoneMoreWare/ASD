/*
cosa fare

visita albero
da profondità l1 a profondità l2

visualizzare tutte le chiavi livello per livello 
*/
/*
Questo codice rappresenta la struttura di un albero di grado fissato N, dove N è il numero di figli che può avere ogni nodo dell'albero. 
Nel caso specifico, l'albero è stato dichiarato come un array di puntatori a nodi di tipo "struct node". 
Ogni nodo dell'albero contiene una chiave intera e un array di puntatori a nodi figli.

La funzione "print_profondita" esegue una visita in profondità dell'albero e stampa la chiave del nodo quando si raggiunge la profondità specificata 
come argomento della funzione. 

La funzione "visitLevelByLevel" utilizza la funzione "print_profondita" per stampare le chiavi del nodo a profondità comprese tra l1 e l2, specificate anche queste come argomenti della funzione.

In sintesi, questo codice permette di visitare l'albero di grado fissato N e di stampare le chiavi dei nodi a profondità comprese tra l1 e l2, livello per livello.
*/

struct node {
	int key; 
	struct node *children[N]; //N in questo caso fissato è il numero di figli per ciascun nodo, se N==2 allora si parla di albero binario
};

void visitLevelByLevel(struct node* root, int l1, int l2){
	for(int i=l1; i <= l2; i++) print_profondita(root, i, 0); 
	
	/*iterazione tra la profondità l1 e l2, passo alla funzione la radice root e la profondità necessaria che è l'iesimo valore 
  che si assume all'interno del for che man mano verra incrementato, ossia aumenta la prodondità, in quanto ci interessa visitare 
  tutte le chiavi tra l1 e l2. Uso una dfs (che non è quella dei grafi). vedi note in basso */
}


void print_profondita(node* root, int profondita_necessaria, int profondita_attuale){
  
	if (root == NULL) return; //non ho nessun albero
  
	if (profondita_necessaria == profondita_attuale){ //quando raggiungo la profondità che mi interessa mi fermo
		printf("%d ", root->chiave);
		return;
	}
	
	// se il figlio esiste visita il figlio in modo ricorsivo, ovviamente devo aumentare la profondità di 1 in quanto scendo nell'albero
	for(int i=0; i<N; i++) print_profondita(root->figli[i], profondita_necessaria, profondita_attuale+1);
}




//approfondimenti https://geode-rat-694.notion.site/Alberi-45faee52e8214fd98b4120f94223e637
