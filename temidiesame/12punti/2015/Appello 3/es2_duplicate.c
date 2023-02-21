

void duplicateLeftChild(struct node *root){
     if(root==NULL) return; //albero vuoto oppure sono arrivato un figlio
     duplicateLeftChild(root->left);
     duplicateLeftChild(root->right);
     root->left=createNode(root->key,root->left,NULL);
}

struct node *createNode(int key,struct node *left,struct node *right){
     struct node *newnode=malloc(sizeof(*newnode));
     newnode->key=key;
     newnode->left=left;
     newnode->right=right; //NULL
     return 
}

//si scende nelle foglie di ciascun sottoalbero, e si crea il nodo identico a se stesso, 
//se non siamo sulle foglie creiamo un nodo che si aggancia al sottoalbero sinistro (vedi esempio tema con 2, il figliosx 2 si aggancia a 1-1
//quindi la condizione di terminazione è la seguente:albero vuoto o sono arrivato a un figlio
//se arrivo a un figlio creo un nuovo figlio sx identico

