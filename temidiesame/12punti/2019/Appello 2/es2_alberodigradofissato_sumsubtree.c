#include <stdio.h>
#include <stdlib.h>

#define N 3

typedef struct treeNode treeNode;
typedef treeNode* nTREE;


struct treeNode {
    int id;
    nTREE children[N];
    float wi;
    float pesosottoalbero;
};

nTREE createTreeNode(int id,float peso);
int maxSum(nTREE t,float *maxwt);
void visit(int *res,struct treeNode *root,float **maxvt);
nTREE createTreeNode(int id,float peso) {
    nTREE node = (nTREE) malloc(sizeof(treeNode));
    node->id = id;
    node->wi=peso;
    node->pesosottoalbero=(float)peso;
    return node;
}

int main() {
    nTREE root = createTreeNode(0,(float)15.2);
    root->children[0] = createTreeNode(1,(float)-8.1);
    root->children[1] = createTreeNode(2,(float)3.0);
    root->children[2] = createTreeNode(3,(float)7.27);

    root->children[0]->children[0] = createTreeNode(4,(float)-20.9);
    root->children[0]->children[0]->children[0] = NULL;
    root->children[0]->children[0]->children[1] = NULL;
    root->children[0]->children[0]->children[2] = NULL;
    root->children[0]->children[1] = createTreeNode(5,(float)-4.0);
    root->children[0]->children[1]->children[0] = NULL;
    root->children[0]->children[1]->children[1] = NULL;
    root->children[0]->children[1]->children[2] = NULL;
    root->children[0]->children[2] = NULL;

    root->children[1]->children[0] = createTreeNode(6,(float)5.3);
    root->children[1]->children[0]->children[0] = createTreeNode(8,(float)2.4);
    root->children[1]->children[0]->children[0]->children[0] = NULL;
    root->children[1]->children[0]->children[0]->children[1] = NULL;
    root->children[1]->children[0]->children[0]->children[2] = NULL;
    root->children[1]->children[0]->children[1] = createTreeNode(9,(float)-5.0);
    root->children[1]->children[0]->children[1]->children[0] = NULL;
    root->children[1]->children[0]->children[1]->children[1] = NULL;
    root->children[1]->children[0]->children[1]->children[2] = NULL;
    root->children[1]->children[0]->children[2] = NULL;
    root->children[1]->children[1] = NULL;
    root->children[1]->children[2] = NULL;

    root->children[2]->children[0] = createTreeNode(7,(float)-10.8);
    root->children[2]->children[0]->children[0] = createTreeNode(10,(float)-3.1);
    root->children[2]->children[0]->children[0]->children[0] = NULL;
    root->children[2]->children[0]->children[0]->children[1] = NULL;
    root->children[2]->children[0]->children[0]->children[2] = NULL;
    root->children[2]->children[0]->children[1] = createTreeNode(11,(float)2.0);
    root->children[2]->children[0]->children[1]->children[0] = NULL;
    root->children[2]->children[0]->children[1]->children[1] = NULL;
    root->children[2]->children[0]->children[1]->children[2] = NULL;
    root->children[2]->children[0]->children[2] = createTreeNode(12,(float)2.8);
    root->children[2]->children[0]->children[2]->children[0] = NULL;
    root->children[2]->children[0]->children[2]->children[1] = NULL;
    root->children[2]->children[0]->children[2]->children[2] = NULL;
    root->children[2]->children[1] = NULL;
    root->children[2]->children[2] = NULL;

    int res;
    float maxwt=0;
    res=maxSum(root,&maxwt);
    printf("%d %f",res,maxwt);


    return 0;
}

int maxSum(nTREE t,float *maxwt){ //wrapper
    int res;
    if(t==NULL) return -1;
    //for(i=0;i<N;i++) countIf(t->children[i]);
    visit(&res,t,&maxwt); 
    return res;
}

/*
     La funzione inizia con un controllo null per verificare che il nodo corrente non sia nullo. Se lo è, la funzione restituisce subito. In caso contrario, la funzione cicla attraverso tutti i figli del nodo corrente e li visita utilizzando la stessa funzione di visita. Questo processo continua finché tutti i nodi dell'albero sono stati visitati.
    Successivamente, la funzione cicla attraverso tutti i figli del nodo corrente e calcola il peso totale sotto ogni nodo. Questo viene fatto sommando il peso totale dei figli a quello del nodo corrente.
*/

//idea: effettuare una sorta di visita post-order in modo tale da assegnare al padre la somma dei valori dei pesi dei suoi figli

void visit(int *res,struct treeNode *root,float **maxvt){

    int i;
    if(root==NULL) return; //risalgo nella ricorsione, condizione di terminazione


    for(i=0;i<N;i++) visit(res,root->children[i],maxvt); //scendo sui figli, rifaccio la visit
    
    for(int j=0;j<N;j++) if(root->children[j]!=NULL) root->pesosottoalbero=root->pesosottoalbero+root->children[j]->pesosottoalbero; //assegno ad ogni nodo la somma dei pesi dei suoi figli, tengo anche conto del peso del nodo stesso
    
    //printf("%d %f %f\n",root->id,root->wi,root->pesosottoalbero);
    if(root->pesosottoalbero>(**maxvt)){
        (*res)=root->id;
        ((**maxvt))=root->pesosottoalbero;
    }

}
