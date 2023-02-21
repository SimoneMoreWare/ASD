#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node *link;

struct node{
    char *sottostringa;
    link next;
};

link spiltStr(char *str);
link newNode(link next,char *val);
void listdisplay(link head);

int main(){
    char str[]="a.bb.ccc.dddd.eeeee.ffffff";
    link head=NULL;
    head=spiltStr(str);
    listdisplay(head);
    return 0;
}

link spiltStr(char *str){
    //Il codice utilizza la funzione strtok per suddividere la stringa in sottostringhe. 
    // La funzione strtok accetta due argomenti: la stringa da suddividere e il carattere di delimitazione. 
    // Restituisce un puntatore alla prima sottostringa e imposta il puntatore interno alla posizione successiva al carattere di delimitazione. 
    // Ogni volta che viene chiamata successivamente con NULL come primo argomento, restituisce la sottostringa successiva fino al prossimo carattere 
    // di delimitazione o alla fine della stringa.
    link head=NULL;
    char *substring = strtok(str, ".");//a

    while (substring != NULL) {
        head= newNode(head,substring);
        substring = strtok(NULL, "."); //bb ccc dddd eeeee
    } 
    return head;
}

link newNode(link next,char *val){
    link x=malloc(sizeof *x);
    if(x==NULL) return NULL;
    else{
        x->sottostringa=strdup(val);
        x->next=(next);
    }
    return x;
}

void listdisplay(link head){
    link x=head;
    while(x->next!=NULL){
        printf("%s ",x->sottostringa);
        x=x->next;
    }
    printf("%s ",x->sottostringa);
}
