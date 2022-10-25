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
 * acquisizione ed inserimento ordinato di nuovi elementi in lista da tastiera
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
#define maxncodice 7
#define maxndatanascita 11

#define filename "../brani.txt"

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

void leggifile();
link SortListIns(struct anagraficanode* head, Item new_data);
void list_display(struct anagraficanode *p);
link newnode(struct anagraficanode* head,Item new_data);
int keygreater(Item a,Item b);
int datatoint(char *data);


int main(){
    leggifile();
    return 0;
}

void leggifile(){
    struct anagraficanode* head=NULL;
    Item dettagliaanagrafica;
    FILE *fpin;
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
            head=SortListIns(head,dettagliaanagrafica);
        }
        list_display(head);
    }else{
        printf("Errore file");
    }
    fclose(fpin);
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

void list_display(struct anagraficanode *p){
    printf("\n");
    while(p!=NULL){
        printf("%s %s %s %s %s %s %d\n",p->val.codice,p->val.nome,p->val.cognome,p->val.datadinascita,p->val.via,p->val.citta,p->val.cap);
        p=p->next;
    }
}
