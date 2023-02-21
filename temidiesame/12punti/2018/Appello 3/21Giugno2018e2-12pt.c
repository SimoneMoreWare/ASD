#include <stdio.h>
#include <stdlib.h>

typedef struct node *link;

struct node{
  int val;
  link left,right;
};

link leggiAlbero(FILE *fp); // funzione aggiuntiva di lettura dell'albero

int diameter(link root);
link diameterR(link root, int *d);
int visita(link root,link z, int len1, int len2, int d);
int main()
{
    FILE *fp,*fp2;
    link root=NULL;
    link root2=NULL;
    int d1,d2;

    if((fp=fopen("alb.txt","r"))==NULL){
        return -1;
    }
    if((fp2=fopen("alb2.txt","r"))==NULL){
        return -2;
    }

    root=leggiAlbero(fp);
    fclose(fp);
    d1=diameter(root);
    printf("Diametro1: %d\n",d1);

    root2=leggiAlbero(fp2);
    fclose(fp2);
    d2=diameter(root2);
    printf("\nDiametro2: %d\n",d2);


    return 0;
}
/* Calcola il diametro dell'albero di radice root passata come parametro */
int diameter(link root){
    int d=0;
    diameterR(root,&d);
    return d;
}
/* Calcola ricorsivamente per ogni nodo dell'albero il diametro relativo */
link diameterR(link root, int *d){
    int diametro=0,len1=0,len2=0;
    link z=NULL; // nodo sentinella

    diametro=visita(root->left,z,len1,len2,diametro); // altezza massima sottoalbero sinistro
    diametro+=visita(root->right,z,len1,len2,diametro); // altezza massima sottoalbero destro

    /* il calcolo dell'altezza viene eseguito a partire dai figli del nodo
       quindi aggiungo il "collegamento" fra la radice e i 2 figli */
    diametro+=2;

    /* Aggiornamento diametro se è maggiore di quello attuale */
    if(diametro>(*d))
        (*d)=diametro;

    /* Condizione di terminazione */
    if(root->left==NULL || root->right==NULL){
        return root;
    }
    diameterR(root->left,d);
    diameterR(root->right,d);

    return root;
}
int visita(link root, link z, int len1, int len2, int d){

    if(root==z){
        return -1;
    }

    len1=visita(root->left,z,len1,len2,d);
    len2=visita(root->right,z,len1,len2,d);

    /* Aggiornamento del valore di altezza massimo */
    if(len1>len2)
        return len1+1;
    else
        return len2+1;

}
/* Legge l'albero da file, ogni nodo è identificato da tre interi(valore,left,right),
   left e right indicano la presenza (=1) o l'assenza (=0) del figlio */
link leggiAlbero(FILE *fp){
    link x=malloc(sizeof(*x));
    int val,left,right;

    fscanf(fp, "%d %d %d", &val,&left,&right);

    x->val=val;

    if(left==0)
        x->left=NULL;
    if(right==0)
        x->right=NULL;
    if(left==1)
        x->left=leggiAlbero(fp);
    if(right==1)
        x->right=leggiAlbero(fp);

    return x;
}
