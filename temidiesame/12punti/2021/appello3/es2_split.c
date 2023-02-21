#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct list *LIST;
typedef struct node *link;

struct node{
    char *s;
    link next;
};

struct list{
    link head;
};
void split(LIST l,char *str,char sep);
link inserimentoincoda(link head,char *val,int k);
int main(){
    LIST l = malloc(sizeof(LIST));
    char str[]="rrrrrrrrr";
    char sep='r';
    split(l,str,sep);
    return 0;
}

void split(LIST l,char *str,char sep){
    l->head=NULL;
    int i;
    char *val= (char *) malloc(strlen(str)*sizeof(char));
    int k=0;
    
    for(i=0;i<strlen(str);i++) {
        
        if (i < strlen(str) - 1) {
            
            if (str[i + 1] != sep) {
                val[k++] = str[i];
            }else{
                val[k++] = str[i];
                l->head = inserimentoincoda(l->head, val, k);
                k = 0;
            }
            
        }else{
            
            val[k++] = str[i];
            l->head = inserimentoincoda(l->head, val, k);
            
        }
        
    }
    
    link tmp=l->head;
    while(tmp!=NULL){
        printf("%s->",tmp->s);
        tmp=tmp->next;
    }
    free(val);
}

link inserimentoincoda(link head,char *val,int k){
    link x = malloc(sizeof *x);
    link tmp;
    if(head==NULL){
        x->s=(char *) malloc((k+1)*sizeof(char));
        strncpy(x->s,val,k);
        x->s[k]='\0';
        x->next=NULL;
        return x;
    }else{
        tmp=head;
        while(tmp->next!=NULL) tmp=tmp->next;
        tmp->next=x;
        x->s=(char *) malloc((k+1)*sizeof(char));
        strncpy(x->s,val,k);
        x->s[k]='\0';
        x->next=NULL;
    }
    return head;
}
