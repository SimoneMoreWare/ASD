/*
 * file composto da un numero indenfinito di righe
 * forma
 * <codice> <nome> <cognome> <data_dinascita> <via> <citta> <cap>
 *      <data_nascita> formato gg/mm/aaaa
 *      <cap> numero intero
 *      <campirimanenti> stringhe senzaspazi max50char
 *      <codice> formato AXXXXX dove X rappresenta una cifra tra 0-9, univoco
 *
 * dettagli anagrafica racchiusi in un opportuno dato di tipo item
 *
 * anagrafica va memorizzata in una lista ordinata per data di nascita
 *      le persone piu giovani appaiono prima nella lista
 *
 * primo passo: inizializzare lista vuota
 *
 * funzionalità
 * acquisizione ed inserimento ordinato di un nuovo elemento in lista da tastiera
 * acquisizione ed inserimento ordinato di nuovi elementi in lista da file di testo
 * ricerca per codice
 * cancellazione con estrazione del dato di un elemento dalla lista previa ricerca per codice
 * cancellazione con estrazione del dato di tutti gli elementi con date comprese tra 2 date lette da testiera
 *      suggerimento: implemtnetare una funzione che estrae e restituisce al programma chiamante il primo degli elementi appartenenti all intervallo
 *                    il programma chiamante itera la chiamata di questa funzione
 *                    stamapando il risultato per tutti gli elementi dell'intervallo
 * stampa della lista su file
 *
 * per le funzioni di ricerca e cancellazione è richiesto che la funzione che opera sulle liste ritorni l'elemento trovato o cancellato al programma chiamante che provvede alla stampa
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 50
#define MAXL 255
#define maxncodice 7
#define maxndatanascita 11

typedef enum comando {r_leggidatastiera,r_leggidafile,r_ricercapercodice,r_cancellacodice,r_cancelladata,r_stampa,r_fine}comando_e;

typedef struct{
    char codice[maxncodice];
    char nome[MAXN];
    char cognome[MAXN];
    char datadinascita[maxndatanascita];
    char via[MAXN];
    char citta[MAXN];
    int cap;
}Item;

typedef struct anagraficanode *link;
struct anagraficanode {
    Item val;
    link next;
};

void menuparola(struct anagraficanode* head);
comando_e leggicomando();

void leggifile(struct anagraficanode** head);
link SortListIns(struct anagraficanode* head, Item new_data);
void list_display(struct anagraficanode *p);
link newnode(struct anagraficanode* head,Item new_data);
int keygreater(Item a,Item b);
int datatoint(char *data);
void inseriscielementodatastiera(struct anagraficanode** head);
link ricercacodice(struct anagraficanode* head);
link SortListDel(link h,link tmp);


int main(){
    struct anagraficanode* head=NULL;
    menuparola(head);
    return 0;
}

void leggifile(struct anagraficanode** head){
    Item dettagliaanagrafica;
    FILE *fpin;
    char filename[MAXL];
    fflush(stdin);
    printf("Inserisci nome file");
    scanf("%s",filename);
    fpin=fopen(filename,"r");
    if(fpin!=NULL){
        while(!feof(fpin)){
            fscanf(fpin,"%s %s %s %s %s %s %d",dettagliaanagrafica.codice,
                   dettagliaanagrafica.nome,
                   dettagliaanagrafica.cognome,
                   dettagliaanagrafica.datadinascita,
                   dettagliaanagrafica.via,
                   dettagliaanagrafica.citta,
                   &(dettagliaanagrafica.cap));
            (*head)=SortListIns(*head,dettagliaanagrafica);
        }
    }else{
        printf("Errore file");
    }
    fclose(fpin);
}

void menuparola(struct anagraficanode* head){
    comando_e codicecomando;
    struct anagraficanode* tmp;
    int continua=1;

    while(continua){
        codicecomando=leggicomando();

        switch (codicecomando){
            case r_leggidatastiera:
                inseriscielementodatastiera(&head);
                list_display(head);
                break;
            case r_leggidafile:
                leggifile(&head);
                list_display(head);
                break;
            case r_ricercapercodice:
                tmp=ricercacodice(head);
                if(tmp!=NULL) printf("%s %s %s %s %s %s %d\n",tmp->val.codice,tmp->val.nome,tmp->val.cognome,tmp->val.datadinascita,tmp->val.via,tmp->val.citta,tmp->val.cap);
                break;
            case r_cancellacodice:
                tmp= ricercacodice(head);
                head=SortListDel(head,tmp);
                list_display(head);
                break;
            case r_cancelladata:
                printf("Inserire la funzione a livello di code 2");
                break;
            case r_stampa:
                list_display(head);
                break;
            case r_fine:
                printf("fine\n");
                continua=0;
                break;
            default:
                printf("comando errato");
        }
    }
}

comando_e leggicomando(){
    comando_e c;
    char cmd[MAXL];
    char *tabella[r_fine+1]={
            "0","1","2","3","4","5","6"
    };
    printf("inserisci comando\n"
           "0 per inserire lista da tastiera\n"
           "1 per inserire lista da file\n"
           "2 per cercare codice\n"
           "3 per cancella: cancella un record per codice\n"
           "4 cancellaintervallo: cancella un intervallo di record compresi fra due date\n"
           "5 stampa\n"
           "6 per chiudere il programma\n");
    fflush(stdin);
    scanf("%s",cmd);
    c=r_leggidatastiera;
    while(c<r_fine && strcmp(cmd,tabella[c])!=0){
        c++;
    }
    return c;
}

link newnode(struct anagraficanode* head,Item new_data){
    struct anagraficanode* nuovo = (struct anagraficanode*) malloc(sizeof(struct anagraficanode));
    //malloc non andata a buon fine
    if(nuovo==NULL){
        printf("Errore nell'allocazione della memoria");
        exit(0);
    }
    //ho un puntatore temporaneo nuovo, uscito dalla funzione viene liberato
    nuovo->val=new_data;
    nuovo->next=(head);//uguale alla vecchia testa
    return nuovo;
}

link SortListIns(struct anagraficanode* head, Item new_data){
    //creo nodo di appoggio di tipo puntatore
    link x,p;
    if((head)==NULL || keygreater(head->val,new_data)){
        return newnode(head,new_data);
    }
    for(x=(head)->next,p=(head);
        x!=NULL && keygreater(new_data,x->val);
        p=x,x=x->next);
    p->next=newnode(x,new_data);
    return head;
}

int keygreater(Item a,Item b){
    return datatoint(a.datadinascita)>  datatoint(b.datadinascita);
}

int datatoint(char *data){
    int res=0;
    if(data[0]!='\0'){
        res=res+(10*(int)((data)[0]-'0')+(int)((data)[1]-'0'))+30*(10*(int)((data)[3]-'0')+(int)((data)[4]-'0'))+365*(1000*(int)((data)[6]-'0')+100*(int)((data)[7]-'0')+10*(int)(data[8]-'0')+(int)(data[9]-'0'));
    }
    //trasformo tutto in secondi
    return res;
}

void inseriscielementodatastiera(struct anagraficanode** head){
    Item dettagliaanagrafica;
    printf("inserisci lista: ");
    scanf("%s %s %s %s %s %s %d",dettagliaanagrafica.codice,
                   dettagliaanagrafica.nome,
                   dettagliaanagrafica.cognome,
                   dettagliaanagrafica.datadinascita,
                   dettagliaanagrafica.via,
                   dettagliaanagrafica.citta,
                   &(dettagliaanagrafica.cap));
    (*head)=SortListIns(*head,dettagliaanagrafica);
    //menuparola(*head);
}

link ricercacodice(struct anagraficanode* head){
    char ricercato[MAXN];
    //codice univoco, appena trovo un valore esco dal while
    if(head==NULL){
        printf("Non c'e' nessun elemento\n");
        return NULL;
    }
    printf("Inserisci codice da ricercare\n");
    fflush(stdin);
    scanf("%s",ricercato);
    while(head!=NULL){
        if(strcmp(ricercato,head->val.codice)==0) return head;
        head=head->next;
    }
    printf("Il codice da te inserito non e' presente in lista\n");
    return NULL;
}

link SortListDel(link head, link tmp) {
    if(head==NULL) return NULL;
    if(tmp->next==NULL) head->next=NULL;
    if(head==tmp) head=tmp->next;
    else head->next=tmp->next;
    free(tmp);
    return head;
}

void list_display(struct anagraficanode *p){
    printf("\n");
    while(p!=NULL){
        printf("%s %s %s %s %s %s %d\n",p->val.codice,p->val.nome,p->val.cognome,p->val.datadinascita,p->val.via,p->val.citta,p->val.cap);
        p=p->next;
    }
}
