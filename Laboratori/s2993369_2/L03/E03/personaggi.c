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
    return NULL;
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
    //free(nuovo);
}

int ifemptylist(tabPg *tabp){
    if(tabp->headPg==NULL){
        printf("lista vuota\n");
        return 1;
    }
    return 0;
}

void ricercacodicepersonaggio(tabPg *tabp){
    nodoPg *nodo;
    nodo=tabp->headPg;
    int flag=1;
    char ricercato[MAXN];
    if(ifemptylist(tabp)) return;
    printf("Inserisci codice da ricercare: ");
    scanf("%s",ricercato);
    while(nodo!=NULL && flag==1){
        if(strcmp(nodo->val.codice,ricercato)==0) {
            flag = 0;
            stampapersonaggiosingolo(nodo);
        }
        nodo=nodo->next;
    }
    if(flag==1) printf("il codice inserito non è presente nella lista\n");
}

void stampapersonaggiosingolo(nodoPg *nodo){
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
    if(nodo->val.equip.inUso!=0){
        printf("Equipaggiamento personaggio\n");
        for(int i=0;i<nodo->val.equip.inUso;i++){
        stampaequippagiamentopersonaggio(nodo,i);
        }
    }
}

void eliminapersonaggio(tabPg *tabp){
    nodoPg *p,*x,*tmp;
    int flag=1;
    char ricercato[MAXN];
    if(ifemptylist(tabp)) return;
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
    int i;
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
        if(nodo->val.equip.inUso!=0){
            printf("Equipaggiamento personaggio\n");
            for(i=0;i<nodo->val.equip.inUso;i++){
                stampaequippagiamentopersonaggio(nodo,i);
            }
        }
        nodo=nodo->next;
        printf("\n");
    }
    printf("Numero Personaggi Attuali : %d\n",tabp->nPg);
}

void stampaequippagiamentopersonaggio(nodoPg *nodo,int i){
    printf("%s %s %d %d %d %d %d %d\n",
           nodo->val.equip.vettEq[i].nome,
           nodo->val.equip.vettEq[i].tipo,
           nodo->val.equip.vettEq[i].stat.hp,
           nodo->val.equip.vettEq[i].stat.mp,
           nodo->val.equip.vettEq[i].stat.atk,
           nodo->val.equip.vettEq[i].stat.def,
           nodo->val.equip.vettEq[i].stat.nag,
           nodo->val.equip.vettEq[i].stat.spr
    );
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

tabPg *aggiungereequipaggiamento(tabPg *tabp, tabInv_t *tabi){
    nodoPg *nodo;
    nodo=tabp->headPg;
    int indexfind;
    char ricercato[MAXN];
    printf("Inserisci codice da ricercare: ");
    scanf("%s",ricercato);
    indexfind=ricercanomeoggetto(tabi);
    if(indexfind==-1 || indexfind==-2){
        printf("Errore nell'inserimentod del nome dell'oggetto");
        return tabp;
    }
    inserireoggettonellequipaggiamento(nodo,tabi,indexfind,ricercato);//nodo viene modificato nella funzione, che modifica tabp
    //stampaoggettotrovato(tabi,indexfind);
    //nodo->val.equip.vettEq[nodo->val.equip.inUso]=tabi->vettInv[indexfind];
    //nodo->val.equip.inUso++;
    return tabp;
}

tabPg *rimuovereequipaggiamento(tabPg *tabp, tabInv_t *tabi){
    nodoPg *nodo;
    nodo=tabp->headPg;
    int indexfind;
    char ricercato[MAXN];
    printf("Inserisci codice personaggio da eliminare: ");
    scanf("%s",ricercato);
    indexfind=ricercanomeoggetto(tabi);
    if(indexfind==-2 || indexfind==-1){
        printf("Oggetto non presente in lista inventario\n");
        return tabp;
    }
    eliminareoggettonellequipaggiamento(nodo,indexfind,ricercato);//nodo viene modificato nella funzione, che modifica tabp
    //stampaoggettotrovato(tabi,indexfind);
    //nodo->val.equip.vettEq[nodo->val.equip.inUso]=tabi->vettInv[indexfind];
    //nodo->val.equip.inUso++;
    return tabp;
}

void inserireoggettonellequipaggiamento(nodoPg *nodo,tabInv_t *tabi, int indexfind, char *ricercato){
    int flag=1;
    while(nodo!=NULL && flag==1){
        if(strcmp(nodo->val.codice,ricercato)==0){
            flag=0;
            if(nodo->val.equip.inUso>=8 || nodo->val.equip.inUso>tabi->nlnv){
                printf("equipaggiamento pieno, impossibile aggiungere oggetti\n");
                return;
            }
            nodo->val.equip.vettEq[nodo->val.equip.inUso]=tabi->vettInv[indexfind];
            nodo->val.equip.inUso++;
        }
        nodo=nodo->next;
    }
    if(flag==1) printf("il codice inserito non è presente nella lista\n");
}

void eliminareoggettonellequipaggiamento(nodoPg *nodo, int indexfind, char *ricercato){
    int flag=1;
    int i;
    while(nodo!=NULL && flag==1){
        if(strcmp(nodo->val.codice,ricercato)==0){
            flag=0;
            if(nodo->val.equip.inUso==0){
                printf("il personaggio non ha oggetti nell'equipaggiamento\n");
                return;
            }
            // shifting degli altri elementi
            for(i=indexfind; i < nodo->val.equip.inUso; i++)
                nodo->val.equip.vettEq[i-1] = nodo->val.equip.vettEq[i];
            nodo->val.equip.inUso--;
        }
        nodo=nodo->next;
    }
    if(flag==1) printf("il codice inserito non è presente nella lista\n");
}

void calcolostat(tabPg *tabp){
    int reshp=0,resmp=0,resatk=0,resdef=0,resnag=0,resspr=0;
    nodoPg *nodo;
    nodo=tabp->headPg;
    int i;
    int flag=1;
    char ricercato[MAXN];
    if(ifemptylist(tabp)) return;
    printf("Inserisci codice da ricercare: ");
    scanf("%s",ricercato);
    while(nodo!=NULL && flag==1){
        if(strcmp(nodo->val.codice,ricercato)==0){
            flag=0;
            reshp=reshp+(nodo->val.stat.hp);
            resmp=resmp+(nodo->val.stat.mp);
            resatk=resatk+(nodo->val.stat.atk);
            resdef=resdef+(nodo->val.stat.def);
            resnag=resnag+(nodo->val.stat.nag);
            resspr=resspr+(nodo->val.stat.spr);

            if(nodo->val.equip.inUso!=0){
                for(i=0;i<nodo->val.equip.inUso;i++){
                    reshp=reshp+nodo->val.equip.vettEq[i].stat.hp;
                    resmp=resmp+nodo->val.equip.vettEq[i].stat.mp;
                    resatk=resatk+nodo->val.equip.vettEq[i].stat.atk;
                    resdef=resdef+nodo->val.equip.vettEq[i].stat.def;
                    resnag=resnag+nodo->val.equip.vettEq[i].stat.nag;
                    resspr=resspr+nodo->val.equip.vettEq[i].stat.spr;
                }
            }

            if(resatk<0) resatk=0; if(resdef<0) resdef=0; if(reshp<0) reshp=0; if(resmp<0) resmp=0; if(resnag<0) resnag=0; if(resspr<0) resspr=0;

            printf("Stat:\n %s %s %s %d %d %d %d %d %d\n",
                   nodo->val.codice,
                   nodo->val.nome,
                   nodo->val.classe,
                   (reshp),
                   (resmp),
                   (resatk),
                   (resdef),
                   (resnag),
                   (resspr));
        }


        nodo=nodo->next;
    }
    if(flag==1) printf("il codice inserito non è presente nella lista\n");
}

void freeTabella(tabPg *tabp) {
    nodoPg *nodo,*p;
    for(nodo = tabp->headPg; nodo != NULL; nodo = p) {
        p = nodo->next;
        free(nodo);
    }
    free(tabp);
}
