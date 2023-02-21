void printpaths(link root,int h,int *path,int altezza_attuale){
    if(root=NULL) return;
    
    if(root->right==NULL && root->left==NULL){
    	path[altezza_attuale] = root->key;
        for(int i=0;i<h;i++) printf("%d ",path[i]);
        printf("\n");
    }
    path[altezza_attuale]=root->key;
    printpaths(root->left,h,path,altezza_attuale+1);
    printpath(root->right,h,path,altezza_attuale+1);
    
    
}

/*
Questo codice implementa una funzione ricorsiva che, dato un albero binario e l'altezza dell'albero, stampa tutti i percorsi dalla radice alle foglie.

La funzione accetta tre parametri:

"root": è il puntatore alla radice dell'albero
"h": è l'altezza dell'albero
"path": è un array che viene utilizzato per memorizzare il percorso attuale dalla radice alla foglia
"altezza_attuale": è l'altezza del nodo corrente nell'albero
La funzione esegue le seguenti operazioni:

Se il nodo corrente è NULL, esce dalla funzione.
Se il nodo corrente è una foglia (ovvero, se non ha figli a sinistra e a destra), stampa il percorso dalla radice alla foglia e quindi esce dalla funzione.
Altrimenti, aggiunge il valore del nodo corrente all'array "path" e chiama ricorsivamente la funzione sui figli a sinistra e a destra del nodo corrente, incrementando l'altezza attuale di 1 ad ogni chiamata ricorsiva.
*/
