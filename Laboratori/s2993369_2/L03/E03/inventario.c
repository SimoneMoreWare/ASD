//
// Created by simone on 11/11/22.
//

#include "inventario.h"

tabInv_t* leggifileinventario(){
    tabInv_t *tutto;
    int i,dim_inventario;
    char namefile[MAXN];
    FILE *fp;
    printf("Inserisci nome file: ");
    scanf("%s",namefile);
    fp=fopen(namefile,"r");
    if(fp==NULL) return NULL;
    fscanf(fp,"%d",&dim_inventario);
    tutto=allocainventario(dim_inventario);
    for(i=0;i<dim_inventario;i++){
        inputinventariofile(fp,&tutto,i);
    }
    tutto->nlnv=dim_inventario;
    fclose(fp);
    return tutto;
}

tabInv_t *allocainventario (int dim_inventario) {
    tabInv_t *ap = malloc(sizeof(tabInv_t));
    ap->maxlnv = dim_inventario;
    ap->nlnv= 0;
    ap->vettInv = malloc(dim_inventario*sizeof(tabInv_t));
    return ap;
}

void inputinventariofile(FILE *fp,tabInv_t **tutto,int i){
    fscanf(fp,"%s %s %d %d %d %d %d %d",
           (*tutto)->vettInv[i].nome,
           (*tutto)->vettInv[i].tipo,
           &((*tutto)->vettInv[i].stat.hp),
           &((*tutto)->vettInv[i].stat.mp),
           &((*tutto)->vettInv[i].stat.atk),
           &((*tutto)->vettInv[i].stat.def),
           &((*tutto)->vettInv[i].stat.nag),
           &((*tutto)->vettInv[i].stat.spr)
           );

}

void stampainventario(tabInv_t *tabi){
    int i;
    for(i=0;i<(tabi->nlnv);i++){
        printf("%s %s %d %d %d %d %d %d\n",
               (tabi)->vettInv[i].nome,
               (tabi)->vettInv[i].tipo,
               ((tabi)->vettInv[i].stat.hp),
               ((tabi)->vettInv[i].stat.mp),
               ((tabi)->vettInv[i].stat.atk),
               ((tabi)->vettInv[i].stat.def),
               ((tabi)->vettInv[i].stat.nag),
               ((tabi)->vettInv[i].stat.spr)
        );
    }
    printf("Dimensioni oggetti %d\n",tabi->nlnv);
}

void ricercanomeoggetto(tabInv_t *tabi){
    int i;
    char ricercato[MAXN];
    int flag=1;
    if(tabi==NULL){
        printf("inventario vuoto\n");
        return;
    }
    printf("Inserisci nome oggetto: ");
    scanf("%s",ricercato);
    for(i=0;i<(tabi->nlnv);i++){ //nel caso ci sono duplicati ne stampo tutti
        if(strcmp(ricercato,tabi->vettInv[i].nome)==0){
            flag=0;
            printf("%s %s %d %d %d %d %d %d\n",
                   (tabi)->vettInv[i].nome,
                   (tabi)->vettInv[i].tipo,
                   ((tabi)->vettInv[i].stat.hp),
                   ((tabi)->vettInv[i].stat.mp),
                   ((tabi)->vettInv[i].stat.atk),
                   ((tabi)->vettInv[i].stat.def),
                   ((tabi)->vettInv[i].stat.nag),
                   ((tabi)->vettInv[i].stat.spr)
            );
        }
    }
    if(flag==1) printf("Il nome inserito non è presente in lista\n");
}
