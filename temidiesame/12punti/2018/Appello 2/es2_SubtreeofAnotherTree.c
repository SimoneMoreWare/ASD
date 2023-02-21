/*
Il codice presentato implementa una funzione per verificare se un albero (subRoot) è un sottoalbero di un altro albero (root). 
La funzione principale è chiamata "isSubtree" e utilizza una funzione di supporto chiamata "check" per verificare se due alberi sono uguali.

La funzione "isSubtree" inizia controllando se entrambi gli alberi sono null, in tal caso restituisce vero. 
In caso contrario controlla se uno dei due alberi è null e in tal caso restituisce falso.

Successivamente, utilizza la funzione "check" per verificare se l'albero radice è uguale al sottoalbero dato. 
Se questa verifica restituisce vero, la funzione "isSubtree" restituirà vero
altrimenti utilizza una tecnica di ricorsione per esplorare tutti i nodi dell'albero radice.

La funzione "isSubtree" viene chiamata due volte, 
una volta sull'albero sinistro del nodo radice 
e una volta sull'albero destro del nodo radice, passando sempre come secondo parametro l'albero subRoot. 

In questo modo la funzione esplorerà tutti i nodi dell'albero radice, e per ogni nodo che incontra, 
chiamerà la funzione "check" per vedere se l'albero sotto quel nodo è uguale al sottoalbero dato. 

Il risultato delle due chiamate alla funzione "isSubtree" viene poi confrontato con un operatore OR, in modo che se una delle due chiamate restituisce true, la funzione "isSubtree" restituirà true, altrimenti restituirà false.

La funzione "check" controlla se due alberi sono uguali. 
Inizia controllando se entrambi gli alberi sono null, in tal caso restituisce vero. 
In caso contrario controlla se entrambi gli alberi non sono null e se i loro valori sono uguali. 
Se questa verifica restituisce vero, utilizza una tecnica di ricorsione per controllare se i sottoalberi sinistro e destro dei due alberi sono uguali.
Se entrambi i controlli restituiscono vero, la funzione "check" restituirà vero, altrimenti restituirà falso.
*/


/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */


bool check(struct TreeNode* root, struct TreeNode* subRoot);



bool isSubtree(struct TreeNode* root, struct TreeNode* subRoot){

    if(root==NULL && subRoot==NULL) return 1;
    if(root==NULL && subRoot!=NULL) return 0;
    if(root!=NULL && subRoot==NULL) return 0;
    
    if(check(root,subRoot)) return 1;
  
    /*
      Questa istruzione effettua una ricorsione sull'albero radice. In questo modo, la funzione esegue una ricorsione su entrambi gli alberi verificando che i valori dei nodi e la struttura degli alberi siano uguali. Se entrambe le chiamate alla funzione "check" restituiscono vero, significa che i due alberi sono uguali e quindi la funzione "check" restituirà vero. Altrimenti, restituirà falso.
      La funzione "isSubtree" viene chiamata due volte, una volta sull'albero sinistro del nodo radice e una volta sull'albero destro del nodo radice,
      passando sempre come secondo parametro l'albero subRoot. 
      In questo modo la funzione esplorerà tutti i nodi dell'albero radice, e per ogni nodo che incontra, chiamerà la funzione "check" per vedere se l'albero sotto quel nodo è uguale al sottoalbero dato. 
      Il risultato delle due chiamate alla funzione "isSubtree" viene poi confrontato con un operatore OR, in modo che se una delle due chiamate restituisce true, la funzione "isSubtree" restituirà true, altrimenti restituirà false.
    */

    return isSubtree(root->left,subRoot) || isSubtree(root->right,subRoot); //per ogni nodo dell root vedo se vi è un sottoalbero

}

/*
In questo modo, la funzione esegue una ricorsione su entrambi gli alberi verificando che i valori dei nodi e la struttura degli alberi siano uguali. 
Se entrambe le chiamate alla funzione "check" restituiscono vero, significa che i due alberi sono uguali e quindi la funzione "check" restituirà vero. 
Altrimenti, restituirà falso.
*/

bool check(struct TreeNode* root, struct TreeNode* subRoot){
    bool i,j;
    
    if(root==NULL && subRoot==NULL) return 1;

    if(root!=NULL && subRoot!=NULL && root->val == subRoot->val){
        return check(root->left,subRoot->left) && check(root->right,subRoot->right);   //ricorro sull albero sinistro e destro 
    }
    return 0; //se non sono uguali i valori o la struttura torno falso
}
