
typedef struct nodeprodotti *linkprodotti;
typedef struct nodeproduttori *linkproduttori;

struct nodeproduttori{
    char *nomeproduttore;
    linkprodotti prodotti;
    linkproduttori next;
};

struct nodeprodotti{
    char *nomeprodotto;
    float prezzo;
    linkprodotti next;
};

void searchProdotto(char *cercaproduttore,char *cercaprodotto, linkproduttori produttori){
     link tmpproduttore=produttori;
     int flagproduttore = 0;
     link tmpprodotto=NULL;
  
     while(tmpproduttore!=NULL && flagproduttore==0){
          if(strcmp(cercaproduttore,tmpproduttore->nomeproduttore)==0){
               flagproduttore=1;
               tmpprodotto=tmpproduttori->prodotti;
          } 
     }
     
     if(flagproduttore==0) return; //produttore non presente in lista
     
     int flagprodotto=0;
     
     while(tmpprodotto!=NULL && flagprodotto==0){
         if(strcmp(cercaprodotto,tmpprodotto->nomeprodotto)==0){
             flagprodotto=1;
             printf("Prezzo del prodotto cercato e' : %f\n",tmpprodotto->prezzo);
         }
     }
     
     if(flagprodotto==0) return; //prodotto non presente in tale lista     
}

/*
La funzione "searchProdotto" è una funzione che cerca un prodotto specifico in una lista di produttori. Prende in input il nome del produttore (cercaproduttore) e il nome del prodotto (cercaprodotto) che si desidera cercare, e la lista di produttori (produttori) in cui cercare.

La funzione inizia scorrendo la lista di produttori, cercando il produttore specificato (cercaproduttore). Se viene trovato, imposta una flag (flagproduttore) a 1 e salva il puntatore alla lista di prodotti del produttore in una variabile temporanea (tmpprodotto). Se il produttore non viene trovato, la funzione termina senza fare nulla.

Successivamente, la funzione scorre la lista di prodotti del produttore (tmpprodotto), cercando il prodotto specificato (cercaprodotto). Se viene trovato, imposta una flag (flagprodotto) a 1 e stampa a schermo il prezzo del prodotto. Se il prodotto non viene trovato, la funzione termina senza fare nulla.
*/
