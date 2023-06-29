#include "skilifts.h"

typedef struct node *link;

struct node{
    Skilift val;
    link next;
};

struct sk_s{
   link head;
};



static Skilifts LISTinit(){
    Skilifts s;
    s=(Skilifts)malloc(sizeof(struct sk_s));
    if(s==NULL) exit(EXIT_FAILURE);
    s->head=NULL;
    return s;
}


static link NEWnode(Skilift s, link next){
    link x=malloc(sizeof(struct node));
    if(x==NULL) exit(EXIT_FAILURE);
    x->val=s;
    x->next=next;
    return x;
}


static link LISTinsertTail(link head, Skilift val){
    link x;
    if(head==NULL)
        return NEWnode(val, NULL);
    for(x=head; x->next!=NULL; x=x->next);
    x->next=NEWnode(val, NULL);
    return head;
}


static Skilift *LISTsearch(Skilifts s, char *skiliftId){
    link x;
    for(x=s->head; x!=NULL; x=x->next){
        if(strcmp(x->val.skiliftId, skiliftId)==0)
            return &x->val;
    }
    return NULL;
}


static void LISTfree(Skilifts s){
    link x, t;
    for(x=s->head; x!=NULL; x=t){
        t=x->next;
        SKILIFTclear(x->val);
        free(x);
    }
    return;
}


Skilifts SKILIFTSinit(){
   return LISTinit();
}


Skilifts SKILIFTSread(FILE *f){
   Skilifts s=SKILIFTSinit();
   Skilift sk;
   sk=SKILIFTread(f);
   while(SKILIFTisNull(sk)==FALSO){
      SKILIFTSadd(s, sk);
      sk=SKILIFTread(f);
   }
   return s;
}


Skilift *SKILIFTSsearch(Skilifts s, char *id){
   return LISTsearch(s, id);
}


void SKILIFTSadd(Skilifts s, Skilift sk){
   s->head=LISTinsertTail(s->head, sk);
   return;
}


void SKILIFTSprint(Skilifts s, FILE *f){
    link x;
    for(x=s->head; x!=NULL; x=x->next){
        SKILIFTprint(x->val, f);
    }
    return;
}


void SKILIFTSfree(Skilifts s){
   LISTfree(s);
   return;
}
