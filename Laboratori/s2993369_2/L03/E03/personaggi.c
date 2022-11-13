//
// Created by simone on 11/11/22.
//

#include "personaggi.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

tabPg *allocazioneinizialepersonaggio(){
    tabPg *nodo=malloc(sizeof(* nodo));
    nodo->headPg=NULL;
    nodo->tailPg=NULL;
    nodo->nPg=0;
    return nodo;
}
tabPg *leggifilepersonaggi(tabPg *tabp){
    char filename[MAXN];
    FILE *fp;
    ItemP personaggi;
    printf("Inserisci nome file ");
    scanf("%s",filename);
    fp=fopen(filename,"r");
    if(fp!=NULL){
        while(!feof(fp)) {
            inputpersonaggifile(fp, &personaggi);
            aggiungipersonaggio(tabp,personaggi);
            //ok
        }
        fclose(fp);
        return tabp;
    }else{
        printf("Errore file personaggi");
    }
    return 0;
}

void inputpersonaggifile(FILE *fp,ItemP *personaggi){
    personaggi->equip.inUso=0;
    fscanf(fp,"%s %s %s %d %d %d %d %d %d\n",
           personaggi->codice,
           personaggi->nome,
           personaggi->classe,
           &(personaggi->stat.hp),
           &(personaggi->stat.mp),
           &(personaggi->stat.atk),
           &(personaggi->stat.def),
           &(personaggi->stat.nag),
           &(personaggi->stat.spr));
}

void aggiungipersonaggio(tabPg *tabp,ItemP personaggi){
    nodoPg *nuovo;
    nuovo=malloc(sizeof(*nuovo));
    if(nuovo==NULL) printf("errore allocazione nuovo nodo personaggio");
    nuovo->val=personaggi; //
    nuovo->next=NULL;
    if(tabp->headPg==NULL){ //primo elemento
        tabp->headPg=tabp->tailPg=nuovo; //la testa punterà al primo elemento della lista cosi come coda
    }else{
        tabp->tailPg->next=nuovo; //l elemento sucessivo del tail è l elemento appena inserito, vedi disegno dal tablet
        tabp->tailPg=nuovo;//la coda punterà all'elemento appena inserito
    }
    tabp->nPg++;//incremento numero di personaggi
}

void ricercacodicepersonaggio(tabPg *tabp){
    nodoPg *nodo;
    nodo=tabp->headPg;
    int flag=1;
    char ricercato[MAXN];
    if(tabp->headPg==NULL){
        printf("lista vuota\n");
        return;
    }
    printf("Inserisci codice da ricercare: ");
    scanf("%s",ricercato);
    while(nodo!=NULL && flag==1){
        if(strcmp(nodo->val.codice,ricercato)==0){
            flag=0;
            printf("%s %s %s %d %d %d %d %d %d\n",
                   nodo->val.codice,
                   nodo->val.nome,
                   nodo->val.classe,
                   (nodo->val.stat.hp),
                   (nodo->val.stat.mp),
                   (nodo->val.stat.atk),
                   (nodo->val.stat.def),
                   (nodo->val.stat.nag),
                   (nodo->val.stat.spr));
        }
        nodo=nodo->next;
    }
    if(flag==1) printf("il codice inserito non è presente nella lista\n");
}

void eliminapersonaggio(tabPg *tabp){
    nodoPg *p,*x,*tmp;
    int flag=1;
    char ricercato[MAXN];
    if(tabp->headPg==NULL){
        printf("lista vuota");
        return;
    }
    printf("Inserisci codice da eliminare: ");
    scanf("%s",ricercato);
    for(x=tabp->headPg,p=NULL;x!=NULL && flag==1;p=x,x=x->next){
        if(strcmp(x->val.codice,ricercato)==0){
            flag=0;
            if(x==tabp->headPg) tabp->headPg=x->next;
            else p->next=x->next;
            tabp->nPg--;
            tmp=x;
            free(tmp);
        }
    }
    if(flag==1) printf("Il codice che vuoi eliminare non esiste\n");
}

void stampapersonaggi(tabPg *tabp){
    nodoPg *nodo;
    nodo=tabp->headPg;
    printf("\n");
    while(nodo!=NULL){
        printf("%s %s %s %d %d %d %d %d %d\n",
               nodo->val.codice,
               nodo->val.nome,
               nodo->val.classe,
               (nodo->val.stat.hp),
               (nodo->val.stat.mp),
               (nodo->val.stat.atk),
               (nodo->val.stat.def),
               (nodo->val.stat.nag),
               (nodo->val.stat.spr));
        nodo=nodo->next;
    }
    printf("Numero Personaggi Attuali : %d\n",tabp->nPg);
}

tabPg *leggitastierapersonaggio(tabPg *tabp){
    ItemP personaggi;
    printf("Inserisci codice/nome/classe hp/mp/atk/def/mag/spr \n");
    inputpersonaggitastiera( &personaggi);
    aggiungipersonaggio(tabp,personaggi);
    return tabp;

}

void inputpersonaggitastiera(ItemP *personaggi){
    personaggi->equip.inUso=0;
    scanf("%s %s %s %d %d %d %d %d %d",
           personaggi->codice,
           personaggi->nome,
           personaggi->classe,
           &(personaggi->stat.hp),
           &(personaggi->stat.mp),
           &(personaggi->stat.atk),
           &(personaggi->stat.def),
           &(personaggi->stat.nag),
           &(personaggi->stat.spr));
}

