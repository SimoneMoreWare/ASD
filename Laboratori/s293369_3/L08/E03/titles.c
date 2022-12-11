//
// Created by simone on 08/12/22.
//

#include "titles.h"

struct title{
    char name[MAXC];
    BST quotazioni;
};

typedef struct node *link;
struct node { Title val; link next; };
struct listtitle { link head; int N; };
static link SortListIns(LISTTITLE l, char new_data[],FILE *fp);
static link newnode(link head,char new_data[], FILE *fp);

LISTTITLE readfile(FILE *fp,LISTTITLE l){
    char nametitolo[MAXC];
    int dimensionetitoli;
    fscanf(fp,"%d\n",&dimensionetitoli);
    for(int i=0;i<dimensionetitoli;i++){
        fscanf(fp,"%s",nametitolo);
        ((l)->head)= SortListIns(l,nametitolo,fp);
        //printf("%s",l->head->val->name);
    }
    list_display(l);
    return l;
    //
}

LISTTITLE LISTinit() {
    LISTTITLE T = malloc(sizeof(LISTTITLE));
    T->head = NULL;
    T->N = 0;
    return T;
}

Title title_init() {
    Title T = malloc(sizeof(Title));
    T->quotazioni=BSTinit();
    return T;
}

static link SortListIns(LISTTITLE l, char new_data[],FILE *fp){
    link x,p;
    if((l->head)==NULL || keygreater(l->head->val->name,new_data)>0){
        l->N++;
        return newnode(l->head,new_data,fp);
    }
    for(x=(l->head)->next,p=(l->head);
        x!=NULL && keygreater(new_data,x->val->name)>0;
        p=x,x=x->next);
    p->next=newnode(x,new_data,fp);
    l->N++;
    return l->head;
}

int keygreater(char *a,char *b){
    return strcmp(a,b);
}

link newnode(link head,char new_data[],FILE *fp){
    struct node* nuovo = (struct node*) malloc(sizeof(struct node));
    nuovo->val = title_init(); //DEVI RICORDATI DI INIZIALIZZARE IL TITOLO ALTRIMENTI CRASHA TUTTO1
    //malloc non andata a buon fine
    if(nuovo==NULL){
        printf("Errore nell'allocazione della memoria");
        exit(0);
    }
    //ho un puntatore temporaneo nuovo, uscito dalla funzione viene liberato1
    strcpy(nuovo->val->name,new_data);
    nuovo->next=(head);//uguale alla vecchia testa
    readbst(&(nuovo->val->quotazioni),fp);

    return nuovo;
}



void list_display(LISTTITLE l){
    printf("\n");
    link tmp=l->head;
    if(tmp==NULL) printf("Non c'è la lista\n");
    while((tmp)!=NULL){
        printf("%s\n",(tmp->val->name));
        treePrintWrapper(tmp->val->quotazioni);
        (tmp)=(tmp)->next;
    }
}

void SearchTitle(LISTTITLE l){
    char searchtitle[MAXC];
    link tmp=l->head;

    printf("Inserisci titolo da ricercare: ");
    scanf("%s",searchtitle);

    while(tmp!=NULL && keygreater(searchtitle,tmp->val->name)>=0){
        if(strcmp(searchtitle,tmp->val->name)==0){
            printf("Titolo trovato\n");
            printf("%s\n",(tmp->val->name));
            treePrintWrapper(tmp->val->quotazioni);
            return;
        }
        (tmp)=(tmp)->next;
    }
    printf("Il titolo inserito non è presente nella lista\n");
}

void SearchTitleQuotationFromDate(LISTTITLE l){
    char searchtitle[MAXC];
    char date[11];
    link tmp=l->head;

    printf("Inserisci titolo da ricercare: ");
    scanf("%s",searchtitle);

    while(tmp!=NULL){
        if(strcmp(searchtitle,tmp->val->name)==0 && keygreater(searchtitle,tmp->val->name)>=0){
            printf("Titolo trovato\n");
            printf("Inserisci data: ");
            scanf("%s",date);
            SearchBSTQuotationFromdate(tmp->val->quotazioni,date);
            return;
        }
        (tmp)=(tmp)->next;
    }
    printf("Il titolo inserito non è presente nella lista\n");
}

void SearchTitleQuotationMINMAXFromRangeDate(LISTTITLE l){

    char searchtitle[MAXC];
    char date1[11];
    char date2[11];
    link tmp=l->head;

    printf("Inserisci titolo da ricercare: ");
    scanf("%s",searchtitle);

    while(tmp!=NULL){
        if(strcmp(searchtitle,tmp->val->name)==0 && keygreater(searchtitle,tmp->val->name)<=0){
            printf("Titolo trovato\n");
            printf("Inserisci data 1: ");
            scanf("%s",date1);
            printf("\nInserisci data 2: ");
            scanf("%s",date2);
            SearchBSTQuotationMINMAXFromRangeDate(tmp->val->quotazioni,date1,date2);
            return;
        }
        (tmp)=(tmp)->next;
    }
    printf("Il titolo inserito non è presente nella lista\n");
}

void SearchTitleQuotationMINMAXFromAllPeriod(LISTTITLE l){

    char searchtitle[MAXC];
    link tmp=l->head;

    printf("Inserisci titolo da ricercare: ");
    scanf("%s",searchtitle);

    while(tmp!=NULL){
        if(strcmp(searchtitle,tmp->val->name)==0 && keygreater(searchtitle,tmp->val->name)<=0){
            printf("Titolo trovato\n");
            SearchBSTQuotationMINMAXFromAllPeriod(tmp->val->quotazioni);
            return;
        }
        (tmp)=(tmp)->next;
    }
    printf("Il titolo inserito non è presente nella lista\n");
}

void BalanceWrapper(LISTTITLE l){
    char searchtitle[MAXC];
    link tmp=l->head;
    int altezzamassima,altezzaminima,soglia;
    printf("Inserisci titolo da ricercare: ");
    scanf("%s",searchtitle);

    while(tmp!=NULL){
        if(strcmp(searchtitle,tmp->val->name)==0 && keygreater(searchtitle,tmp->val->name)<=0){
            printf("Titolo trovato\n");
            printf("Inserisci soglia S: ");
            scanf("%d",&soglia);
            altezzamassima=AltezzaAlberoMassimaWrapper(tmp->val->quotazioni);
            altezzaminima=AltezzaAlberoMinimaWrapper(tmp->val->quotazioni);
            if(altezzamassima/altezzaminima > soglia){
                printf("Altezza finale: %d: | Altezza mnima: %d \n",altezzamassima-1,altezzaminima-1);
                BalanceBST(tmp->val->quotazioni);
            }else {
                printf("Non c'è bisogno di bilanciare\n");
            }
            return;
        }
        (tmp)=(tmp)->next;
    }
    printf("Il titolo inserito non è presente nella lista\n");
}


void TITOLOfree(Title t){
    BSTQUOTfree(t->quotazioni);
}

void LISTfree(LISTTITLE l){
    link x, y,tmp;
    for(x = l->head; x != NULL; x = y){
        tmp=x;
        y = x->next;
        TITOLOfree(tmp->val);
        free(tmp);
    }
    free(l);
}


