#include "autorizzazioniSciatore.h"
#include <string.h>

//AUTORIZZAZIONE SCIATORE
AutorizzazioneS AUTORIZZAZIONEScrea(char *skilift, char *time){
    AutorizzazioneS as;
    strcpy(as.skilift, skilift);
    strcpy(as.time, time);
    return as;
}


void AUTORIZZAZIONESsetOra(AutorizzazioneS *as, char *time){
    strcpy(as->time, time);
    return;
}


AutorizzazioneS AUTORIZZAZIONESsetNull(){
    AutorizzazioneS as;
    strcpy(as.skilift, "");
    strcpy(as.time, "");
    return as;
}


void AUTORIZZAZIONESprint(AutorizzazioneS as, FILE *f){
    fprintf(f, "\tSkilift: %s - Ora: %s\n", as.skilift, as.time);
    return;
}




//AUTORIZZAZIONI SCIATORE
typedef struct NODE *LINK;

struct NODE{
   AutorizzazioneS val;
   LINK next;
};

struct as_s{
   LINK head;
   int size;
};



static AutorizzazioniS LISTinit(){
    AutorizzazioniS s;
    s=(AutorizzazioniS)malloc(sizeof(struct as_s));
    if(s==NULL) exit(EXIT_FAILURE);
    s->head=NULL;
    s->size=0;
    return s;
}


static LINK NEWnode(AutorizzazioneS s, LINK next){
    LINK x=malloc(sizeof(struct NODE));
    if(x==NULL) exit(EXIT_FAILURE);
    x->val=s;
    x->next=next;
    return x;
}


static LINK LISTinsertTail(LINK head, AutorizzazioneS val){
    LINK x;
    if(head==NULL)
        return NEWnode(val, NULL);
    for(x=head; x->next!=NULL; x=x->next);
    x->next=NEWnode(val, NULL);
    return head;
}


static AutorizzazioneS *LISTsearch(AutorizzazioniS s, char* skilift){
    LINK x;
    for(x=s->head; x!=NULL; x=x->next){
        if(strcmp(x->val.skilift, skilift)==0)
            return &x->val;
    }
    return NULL;
}


static void LISTfree(AutorizzazioniS s){
    LINK x, t;
    for(x=s->head; x!=NULL; x=t){
        t=x->next;
        free(x);
    }
    return;
}


AutorizzazioniS AUTORIZZAZIONISinit(){
    return LISTinit();
}


AutorizzazioneS *AUTORIZZAZIONISsearch(AutorizzazioniS as, char *skilift){
    return LISTsearch(as, skilift);
}


void AUTORIZZAZIONISadd(AutorizzazioniS as, AutorizzazioneS a){
    as->head=LISTinsertTail(as->head, a);
    return;
}


int AUTORIZZAZIONISsize(AutorizzazioniS as){
    return as->size;
}


void AUTORIZZAZIONISprint(AutorizzazioniS as, FILE *f){
    LINK x;
    for(x=as->head; x!=NULL; x=x->next){
        AUTORIZZAZIONESprint(x->val, f);
    }
    return;
}


void AUTORIZZAZIONISfree(AutorizzazioniS as){
    LISTfree(as);
    return;
}
