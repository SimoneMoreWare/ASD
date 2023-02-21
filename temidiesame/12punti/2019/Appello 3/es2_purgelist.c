typedef struct node* link;

struct node {
    char key;
    link next;
};

/*
    idea 
    usare inserimento in coda
    scorro sulla lista 1.
    
    se trovo una parentesi cambio valore alla variabile di alcuni flag in modo tale che in seguito non inserisco in coda tutto cio che sta dentro le parentesi
    dopo la prima parentesi ci inserisco in coda un asterisco
    se trovo la parentesi chiusa cambio variabile di alcuni flag
    
    in generale inscerisco in coda il valore corrente della prima lista
    
    si inserisce in coda perchè l ordine della sequenza deve essere mantenuto
*/

link purgeList(link head1){
    link head2=NULL;
    link tmp;
    int apertaparentesi=0;
    int flagasterisco=0;

    tmp = head1;

    while(tmp!=NULL){ //scorro su lista 1

        if(tmp->key=='('){
            apertaparentesi=1;
            flagasterisco=0;
            head2=inserimentoincoda(head2,'(');
        }

        if(apertaparentesi==1 && flagasterisco==0){
            flagasterisco=1;
            head2=inserimentoincoda(head2,'*');
        }

        if(tmp->key==')'){
            apertaparentesi=0;
        }

        if(apertaparentesi==0){
            head2=inserimentoincoda(head2,tmp->key);
        }

        tmp=tmp->next;
    }

    return head2;
}

link inserimentoincoda(link head,char key){
    link x;  //variabile di appoggio
    if(head==NULL) return newNode(NULL,key); //lista vuota, inserisco al primo elemento

    x=head;

    while(x->next!=NULL) x=x->next; //scorro su tutta la lista fin quando arrivo all'ultimo elemento

    x->next = newNode(NULL,key); //arrivato all ultimo elemento creo nuovo elemento 

    return head;

}


link newNode(link next,char key){
    link new = malloc(sizeof(link)); //si usa la malloc in quanto devo "occupare" nuova memoria

    if(new==NULL) return NULL; //errore nella malloc
    else{
        new->key=key; //inserisco al nuovo nodo il valore che voglio inserire
        new->next=next; //chi è il successivo del nodo? nell'inserimento in coda è null
    }

    return new;
}
