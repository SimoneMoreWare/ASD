//struttura C

typedef struct nodo *link;

struct{
    char *cognome;
    char *nome;
    int votoesame;
    link leftchild;
    link rightsibling;
}nodo;

//visita ricorsiva
void visita(link root){
    if(root=NULL) return;
    printf("Cognome: %s, Nome: %s, Voto: %d\n", root->cognome, root->nome, root->voto);
    visita(root->leftchild);
    visita(root->rightsibling);
}
