link mirror(link root) {
    if(root==NULL) return NULL;
    link new_node = malloc(sizeof(struct node)); 
    new_node->data = root->data;
    new_node->left = mirror(root->right);
    new_node->right = mirror(root->left);
    return new_node;
}

/*
allora l ho fatto

ho pensato a una sorta di visita in post order

link mirror(link root) {
    if(root==NULL) return NULL;
    link new_node = malloc(sizeof(struct node)); 
    new_node->data = root->data;
    new_node->left = mirror(root->right);
    new_node->right = mirror(root->left);
    return new_node;
}


La funzione inizia controllando se l'albero è vuoto.

Se l'albero non è vuoto, la funzione alloca memoria per un nuovo nodo. 

Il nuovo nodo viene quindi inizializzato con i valori della chiave del nodo corrente dell'albero originale. (mi raccomando a questo passo perchè è fondamentale allocare memoria)

Successivamente, la funzione richiama se stessa sui figli destro e sinistro del nodo corrente dell'albero originale. 

La chiamata ricorsiva per il figlio destro viene assegnata al figlio sinistro del nuovo nodo, mentre la chiamata ricorsiva per il figlio sinistro viene assegnata al figlio destro del nuovo nodo.

In questo modo, i figli sinistro e destro vengono scambiati nella copia dell'albero.

Infine, la funzione restituisce il puntatore alla radice del nuovo albero speculare.

finite le ricorsioni mirror restituisce il puntatore alla radice dell'albero speculare.
*/
